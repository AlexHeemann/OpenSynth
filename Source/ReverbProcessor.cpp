/*
  ==============================================================================

    ReverbProcessor.cpp
    Created: 24 Nov 2016 8:05:38pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "ReverbProcessor.h"
#include "ReverbParameterContainer.h"
#include "ModulationMatrix.h"

ReverbProcessor::ReverbProcessor(ModulationMatrix* modulationMatrix, int bufferSize) : Processor(modulationMatrix, bufferSize)
{
    
    
}

template <typename FloatType>
void ReverbProcessor::processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples)
{
    ReverbDouble::Parameters parameters;
    parameters.roomSize = reverbParameterContainer->getReverbSizeParameter()->get();
    parameters.damping = reverbParameterContainer->getReverbDampingParameter()->get();
    parameters.dryLevel = reverbParameterContainer->getReverbDryParameter()->get();
    parameters.wetLevel = reverbParameterContainer->getReverbWetParameter()->get();
    parameters.width = reverbParameterContainer->getReverbWidthParameter()->get();
    
    reverb.setParameters(parameters);
    
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
