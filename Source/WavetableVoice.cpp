/*
  ==============================================================================

    WavetableVoice.cpp
    Created: 6 Oct 2016 9:35:15am
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "WavetableVoice.h"

WavetableVoice::WavetableVoice(Wavetable& wavetable) : phaseIncrement(0.0), wavetable(wavetable)
{
    
}

WavetableVoice::~WavetableVoice()
{
    delete envelopeGenerator;
}

void WavetableVoice::setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator)
{
    this->envelopeGenerator = envelopeGenerator;
    this->envelopeGenerator->setSampleRate(getSampleRate());
    this->envelopeGenerator->resetEnvelope();
    ampProcessor.setEnvelopeGenerator(envelopeGenerator);
}

void WavetableVoice::setWavetable(Wavetable& wavetable)
{
    this->wavetable = wavetable;
}

void WavetableVoice::startNote(int midiNoteNumber, float velocity,
               SynthesiserSound* sound,
               int currentPitchWheelPosition)
{
    currentPhase = 0.0;
    level = velocity * 0.15;
    releaseCounter = 0;
    
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    double frqRad = (2.0 * double_Pi) / getSampleRate();
    
    phaseIncrement = frqRad * frequency;
    
    if (envelopeGenerator != nullptr)
    {
        envelopeGenerator->resetEnvelope();
    }
}

void WavetableVoice::stopNote(float velocity, bool allowTailOff)
{
    if (allowTailOff && envelopeGenerator != nullptr && envelopeGenerator->releaseRate->get() > 0)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.
        
        // we only need to begin a tail-off if it's not already doing so - the
        // stopNote method could be called more than once.
        if (releaseCounter == 0)
        {
            releaseCounter = envelopeGenerator->releaseRate->get() * getSampleRate();
            envelopeGenerator->setEnvelopeState(EnvelopeGenerator::EnvelopeStateRelease);
        }
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..
        clearCurrentNote();
        phaseIncrement = 0.0;
        currentPhase = 0.0;
    }
}

template <typename FloatType>
void WavetableVoice::processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples)
{
    envelopeGenerator->calculateEnvelopeBuffer(numSamples);
    // This buffer is used to calculate all the samples for this voice, it then gets added to the overall output buffer of the synth
    AudioBuffer<FloatType> localBuffer = AudioBuffer<FloatType>(outputBuffer.getNumChannels(), outputBuffer.getNumSamples());
    localBuffer.clear();
    
    if (phaseIncrement != 0.0)
    {
        float* subtable = wavetable.getSubtableForFrequency(frequency);
        int tableSize = wavetable.getTableSize();
        double twoPi = 2.0 * double_Pi;
        if (releaseCounter > 0)
        {
            for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
            {
                int index = (int)((currentPhase / twoPi) * tableSize);
                FloatType currentSample = level * subtable[index];
                
                for (int channel = 0; channel < localBuffer.getNumChannels(); channel++)
                {
                    localBuffer.setSample(channel, sampleIdx, currentSample);
                }
                
                currentPhase += phaseIncrement;
                if (currentPhase >= twoPi)
                {
                    currentPhase -= twoPi;
                }
                releaseCounter--;
                
                if (releaseCounter <= 0)
                {
                    clearCurrentNote();
                    phaseIncrement = 0.0;
                    currentPhase = 0.0;
                    break;
                }
            }
        }
        else
        {
            for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
            {
                int index = (int)((currentPhase / twoPi) * tableSize);
                FloatType currentSample = level * subtable[index];
                
                for (int channel = 0; channel < localBuffer.getNumChannels(); channel++)
                {
                    localBuffer.setSample(channel, sampleIdx, currentSample);
                }
                
                currentPhase += phaseIncrement;
                if (currentPhase >= twoPi)
                {
                    currentPhase -= twoPi;
                }
            }
        }
        ampProcessor.renderNextBlock(localBuffer, localBuffer, startSample, numSamples);
    }
    
    // Add samples from this voice to the output buffer
    for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
    {
        for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample + sampleIdx, localBuffer.getSample(channel, sampleIdx));
        }
    }
}
