/*
  ==============================================================================

    AmpProcessor.cpp
    Created: 6 Oct 2016 2:33:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "AmpProcessor.h"
#include "AmpParameterContainer.h"
#include "ModulationMatrix.h"

AmpProcessor::AmpProcessor(ModulationMatrix* modulationMatrix, int bufferSize) : Processor(modulationMatrix, bufferSize)
{
}

template <typename FloatType>
void AmpProcessor::processBuffer(AudioBuffer<FloatType> &buffer, int startSample, int numSamples)
{
    const float gainModulation = modulationMatrix->getValueForDestinationID(parameterContainer->getGainParameterID());
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        FloatType* const channelData = buffer.getWritePointer(channel);
        const float localLevel = parameterContainer->getGainParameter()->get() * gainModulation;
        
        for (int sample = 0; sample < numSamples; sample++)
        {
            channelData[sample] *= localLevel;
        }
    }
}
