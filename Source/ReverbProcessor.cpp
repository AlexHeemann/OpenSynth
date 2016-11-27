/*
  ==============================================================================

    ReverbProcessor.cpp
    Created: 24 Nov 2016 8:05:38pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "ReverbProcessor.h"

ReverbProcessor::ReverbProcessor()
{
    
    
}

template <typename FloatType>
void ReverbProcessor::processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples)
{
//    ReverbDouble::Parameters parameters;
//    parameters.roomSize = reverbSize->get();
//    parameters.damping = reverbDamping->get();
//    parameters.dryLevel = reverbDryLevel->get();
//    parameters.wetLevel = reverbWetLevel->get();
//    parameters.width = reverbWidth->get();
//    
//    reverb.setParameters(parameters);
    
    if (buffer.getNumChannels() >= 2)
    {
        reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), numSamples);
    }
    else
    {
        reverb.processMono(buffer.getWritePointer(0), numSamples);
    }
}

void ReverbProcessor::setSampleRate(const int sampleRate)
{
    this->sampleRate = sampleRate;
    reverb.setSampleRate(sampleRate);
}

void ReverbProcessor::reset()
{
    reverb.reset();
}
