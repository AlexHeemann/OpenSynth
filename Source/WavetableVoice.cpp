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
    
}

void WavetableVoice::setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator)
{
    this->envelopeGenerator = envelopeGenerator;
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
    
    envelopeGenerator->resetEnvelope();
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
    if (phaseIncrement != 0.0)
    {
        float* subtable = wavetable.getSubtableForFrequency(frequency);
        int tableSize = wavetable.getTableSize();
        double twoPi = 2.0 * double_Pi;
        if (releaseCounter > 0)
        {
            while (--numSamples >= 0)
            {
                int index = (int)((currentPhase / twoPi) * tableSize);
                FloatType currentSample = level * subtable[index];
                
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);
                
                currentPhase += phaseIncrement;
                if (currentPhase >= twoPi)
                {
                    currentPhase -= twoPi;
                }
                ++startSample;
                releaseCounter--;
                
                if (releaseCounter <= 0)
                {
                    clearCurrentNote();
                    currentPhase = 0.0;
                    phaseIncrement = 0.0;
                    break;
                }
            }
        }
        else
        {
            while (--numSamples >= 0)
            {
                int index = (int)((currentPhase / twoPi) * tableSize);
                FloatType currentSample = level * subtable[index];
                
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);
                
                currentPhase += phaseIncrement;
                if (currentPhase >= twoPi)
                {
                    currentPhase -= twoPi;
                }
                ++startSample;
            }
        }
    }
}
