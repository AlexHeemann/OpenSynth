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

const String AmpProcessor::Constants::Identifiers::Amp = "amp";
const String AmpProcessor::Constants::Identifiers::Gain = "gain";
const String AmpProcessor::Constants::Names::Amp = "Master Gain";
const String AmpProcessor::Constants::Names::Gain = "Gain";

AmpProcessor::AmpProcessor(int ID,
                           ModulationMatrix* modulationMatrix,
                           AudioProcessorValueTreeState& audioProcessorValueTreeState,
                           IDManager& idManager,
                           int bufferSize) : Processor(ID,
                                                       modulationMatrix, audioProcessorValueTreeState,
                                                       idManager,
                                                       bufferSize)
{
    audioProcessorValueTreeState.createAndAddParameter(gainParameterStringID(),
                                                       Constants::Names::Gain,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.3f,
                                                       nullptr,
                                                       nullptr);
}

String AmpProcessor::name() const
{
    return Constants::Names::Amp;
}

String AmpProcessor::stringIdentifier() const
{
    return Constants::Identifiers::Amp;
}

String AmpProcessor::gainParameterStringID() const
{
    return Constants::Identifiers::Gain;
}

template <typename FloatType>
void AmpProcessor::processBuffer(AudioBuffer<FloatType> &buffer, int startSample, int numSamples)
{
    const float gainModulation = modulationMatrix->getValueForDestinationID(gainParameterID);
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        FloatType* const channelData = buffer.getWritePointer(channel);
        const float gain = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Gain);
        const float localLevel = gain * gainModulation;
        
        for (int sample = 0; sample < numSamples; sample++)
        {
            channelData[sample] *= localLevel;
        }
    }
    
    if (output != nullptr)
    {
        output->renderNextBlock(buffer, startSample, numSamples);
    }
}
