/*
  ==============================================================================

    AmpProcessor.cpp
    Created: 6 Oct 2016 2:33:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "AmpProcessor.h"

AmpProcessor::AmpProcessor()
{
}

template <typename FloatType>
void AmpProcessor::processBuffer(AudioBuffer<FloatType> &buffer, AudioBuffer<FloatType>& delayBuffer, int startSample, int numSamples)
{
    bool isModulated = envelopeGenerator != nullptr && envelopeGenerator->envelopeBuffer.size() >= numSamples;
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        FloatType* const channelData = buffer.getWritePointer(channel);
        const float localLevel = level->get();
        if (isModulated)
        {
            std::vector<double>& envelopeBuffer = envelopeGenerator->envelopeBuffer;
            for (int sample = 0; sample < numSamples; sample++)
            {
                channelData[sample + startSample] *= localLevel * envelopeBuffer[sample];
            }
        }
        else
        {
            for (int sample = 0; sample < numSamples; sample++)
            {
                channelData[sample + startSample] *= localLevel;
            }
        }
    }
}
