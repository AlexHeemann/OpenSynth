/*
  ==============================================================================

    WavetableVoice.cpp
    Created: 6 Oct 2016 9:35:15am
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "WavetableVoice.h"
#include "OscillatorParameterContainer.h"
#include "FilterParameterContainer.h"
#include "ProcessorManager.h"

WavetableVoice::WavetableVoice(int bufferSize) : audioBuffer(AudioBuffer<float>(2, bufferSize))
{
    processorManager = new ProcessorManager();
}

WavetableVoice::~WavetableVoice()
{
}

void WavetableVoice::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    modulationMatrix->setSampleRateForModulators(sampleRate);
    processorManager->setSampleRateForOscillators(sampleRate);
}

void WavetableVoice::startNote(int midiNoteNumber, float velocity,
               SynthesiserSound* sound,
               int currentPitchWheelPosition)
{
    releaseCounter = 0;
    
    modulationMatrix->resetModulators();
    processorManager->resetProcessors();
}

void WavetableVoice::stopNote(float velocity, bool allowTailOff)
{
    EnvelopeGenerator* ampEnvelope = modulationMatrix->getAmpEnvelope().get();
    if (allowTailOff && ampEnvelope != nullptr && ampEnvelope->getReleaseRate() > 0)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.
        
        // we only need to begin a tail-off if it's not already doing so - the
        // stopNote method could be called more than once.
        if (releaseCounter == 0)
        {
            releaseCounter = ampEnvelope->getReleaseRate() * getSampleRate();
            modulationMatrix->setEnvelopeState(EnvelopeStateRelease);
        }
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..
        clearCurrentNote();
        processorManager->resetOscillators();
    }
}

void WavetableVoice::resizeAndClearAudioBuffer(int numSamples)
{
    if (numSamples != audioBuffer.getNumSamples())
    {
        audioBuffer.setSize(2, numSamples);
    }
    audioBuffer.clear();
}

template <typename FloatType>
void WavetableVoice::processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples)
{
    modulationMatrix->calculateModulation(numSamples);
    modulationMatrix->clear();
    modulationMatrix->writeModulation();
    modulationMatrix->process();
 
    resizeAndClearAudioBuffer(numSamples);
    processorManager->setNoteForOscillators(getCurrentlyPlayingNote());
    
    if (releaseCounter > 0)
    {
        for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
        {
            if (--releaseCounter <= 0)
            {
                clearCurrentNote();
                break;
            }
        }
    }

    processorManager->renderNextBlock(audioBuffer, startSample, numSamples);
    
    // Add samples from this voice to the output buffer
    for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
    {
        for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample + sampleIdx, audioBuffer.getSample(channel, sampleIdx));
        }
    }
}
