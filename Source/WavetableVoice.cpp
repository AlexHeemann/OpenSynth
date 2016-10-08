/*
  ==============================================================================

    WavetableVoice.cpp
    Created: 6 Oct 2016 9:35:15am
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "WavetableVoice.h"

WavetableVoice::WavetableVoice(Wavetable* wavetable) : phaseIncrement1(0.0), phaseIncrement2(0.0), osc1Wavetable(wavetable), osc2Wavetable(wavetable)
{
    
}

WavetableVoice::~WavetableVoice()
{
    delete ampEnvelopeGenerator;
    delete filterEnvelopeGenerator;
}

void WavetableVoice::setAmpEnvelopeGenerator(EnvelopeGenerator* ampEnvelopeGenerator)
{
    this->ampEnvelopeGenerator = ampEnvelopeGenerator;
    this->ampEnvelopeGenerator->setSampleRate(getSampleRate());
    this->ampEnvelopeGenerator->resetEnvelope();
    ampProcessor.setEnvelopeGenerator(ampEnvelopeGenerator);
}

void WavetableVoice::setFilterEnvelopeGenerator(EnvelopeGenerator *filterEnvelopeGenerator)
{
    this->filterEnvelopeGenerator = filterEnvelopeGenerator;
    this->filterEnvelopeGenerator->setSampleRate(getSampleRate());
    this->filterEnvelopeGenerator->resetEnvelope();
    filterProcessor.setEnvelopeGenerator(filterEnvelopeGenerator);
}

void WavetableVoice::setOsc1Wavetable(Wavetable* wavetable)
{
    this->osc1Wavetable = wavetable;
}

void WavetableVoice::setOsc2Wavetable(Wavetable* wavetable)
{
    this->osc2Wavetable = wavetable;
}

void WavetableVoice::startNote(int midiNoteNumber, float velocity,
               SynthesiserSound* sound,
               int currentPitchWheelPosition)
{
    currentPhase1 = 0.0;
    currentPhase2 = 0.0;
    level = velocity * 0.15;
    releaseCounter = 0;
    
    frequency1 = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    frequency2 = frequency1;
    frqRad = (2.0 * double_Pi) / getSampleRate();
    
    calculatePhaseIncrement();
    
    if (ampEnvelopeGenerator != nullptr)
    {
        ampEnvelopeGenerator->resetEnvelope();
    }
    if (filterEnvelopeGenerator != nullptr)
    {
        filterEnvelopeGenerator->resetEnvelope();
    }
}

void WavetableVoice::calculatePhaseIncrement()
{
    phaseIncrement1 = frqRad * frequency1;
    phaseIncrement2 = frqRad * frequency2;
}

void WavetableVoice::stopNote(float velocity, bool allowTailOff)
{
    if (allowTailOff && ampEnvelopeGenerator != nullptr && ampEnvelopeGenerator->releaseRate->get() > 0)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.
        
        // we only need to begin a tail-off if it's not already doing so - the
        // stopNote method could be called more than once.
        if (releaseCounter == 0)
        {
            releaseCounter = ampEnvelopeGenerator->releaseRate->get() * getSampleRate();
            ampEnvelopeGenerator->setEnvelopeState(EnvelopeGenerator::EnvelopeStateRelease);
            filterEnvelopeGenerator->setEnvelopeState(EnvelopeGenerator::EnvelopeStateRelease);
        }
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..
        clearCurrentNote();
        phaseIncrement1 = 0.0;
        currentPhase1 = 0.0;
        phaseIncrement2 = 0.0;
        currentPhase2 = 0.0;
    }
}

template <typename FloatType>
void WavetableVoice::processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples)
{
    ampEnvelopeGenerator->calculateEnvelopeBuffer(numSamples);
    filterEnvelopeGenerator->calculateEnvelopeBuffer(numSamples);
    // This buffer is used to calculate all the samples for this voice, it then gets added to the overall output buffer of the synth
    AudioBuffer<FloatType> localBuffer = AudioBuffer<FloatType>(outputBuffer.getNumChannels(), outputBuffer.getNumSamples());
    localBuffer.clear();
    float localOscMix = oscMix->get();
 
    int currentNote = getCurrentlyPlayingNote();
    if (currentNote >= 0)
    {
        frequency1 = MidiMessage::getMidiNoteInHertz(currentNote + osc1Semi->get());
        frequency2 = MidiMessage::getMidiNoteInHertz(currentNote + osc2Semi->get());
        calculatePhaseIncrement();
    }
    
    if (phaseIncrement1 != 0.0 && phaseIncrement2 != 0.0)
    {
        float* subtable1 = osc1Wavetable->getSubtableForFrequency(frequency1);
        int tableSize1 = osc1Wavetable->getTableSize();
        
        float* subtable2 = osc2Wavetable->getSubtableForFrequency(frequency2);
        int tableSize2 = osc2Wavetable->getTableSize();
        
        double twoPi = 2.0 * double_Pi;
        if (releaseCounter > 0)
        {
            for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
            {
                int index1 = (int)((currentPhase1 / twoPi) * tableSize1);
                FloatType currentSample1 = level * subtable1[index1] * (1 - localOscMix);
                
                int index2 = (int)((currentPhase2 / twoPi) * tableSize2);
                FloatType currentSample2 = level * subtable2[index2] * localOscMix;
                
                for (int channel = 0; channel < localBuffer.getNumChannels(); channel++)
                {
                    localBuffer.setSample(channel, sampleIdx, currentSample1 + currentSample2);
                }
                
                currentPhase1 += phaseIncrement1;
                if (currentPhase1 >= twoPi)
                {
                    currentPhase1 -= twoPi;
                }
                currentPhase2 += phaseIncrement2;
                if (currentPhase2 >= twoPi)
                {
                    currentPhase2 -= twoPi;
                }
                releaseCounter--;
                
                if (releaseCounter <= 0)
                {
                    clearCurrentNote();
                    phaseIncrement1 = 0.0;
                    currentPhase1 = 0.0;
                    phaseIncrement2 = 0.0;
                    currentPhase2 = 0.0;
                    break;
                }
            }
        }
        else
        {
            for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
            {
                int index1 = (int)((currentPhase1 / twoPi) * tableSize1);
                FloatType currentSample1 = level * subtable1[index1] * (1 - localOscMix);
                
                int index2 = (int)((currentPhase2 / twoPi) * tableSize2);
                FloatType currentSample2 = level * subtable2[index2] * localOscMix;
                
                for (int channel = 0; channel < localBuffer.getNumChannels(); channel++)
                {
                    localBuffer.setSample(channel, sampleIdx, currentSample1 + currentSample2);
                }
                
                currentPhase1 += phaseIncrement1;
                if (currentPhase1 >= twoPi)
                {
                    currentPhase1 -= twoPi;
                }
                currentPhase2 += phaseIncrement2;
                if (currentPhase2 >= twoPi)
                {
                    currentPhase2 -= twoPi;
                }
            }
        }
        ampProcessor.renderNextBlock(localBuffer, localBuffer, startSample, numSamples);
        filterProcessor.renderNextBlock(localBuffer, localBuffer, startSample, numSamples);
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
