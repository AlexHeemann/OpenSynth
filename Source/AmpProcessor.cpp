/*
  ==============================================================================

    AmpProcessor.cpp
    Created: 6 Oct 2016 2:33:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "AmpProcessor.h"

void AmpProcessor::setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator)
{
    this->envelopeGenerator = envelopeGenerator;
}

EnvelopeGenerator* AmpProcessor::getEnvelopeGenerator()
{
    return envelopeGenerator;
}

void AmpProcessor::setLevel(float level)
{
    this->level = level;
}

float AmpProcessor::getLevel()
{
    return level;
}

template <typename FloatType>
void AmpProcessor::process(AudioBuffer<FloatType> &buffer, juce::MidiBuffer &midiMessages, AudioBuffer<FloatType> &delayBuffer)
{
    bool isModulated = envelopeGenerator != nullptr;
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        FloatType* const channelData = buffer.getWritePointer(channel);
        isModulated = isModulated && envelopeGenerator->envelopeBuffer.size() >= buffer.getNumSamples();
        if (isModulated)
        {
            std::vector<double> envelopeBuffer = envelopeGenerator->envelopeBuffer;
            for (int sample = 0; sample < buffer.getNumSamples(); sample++)
            {
                channelData[sample] *= level * envelopeBuffer[sample];
            }
        }
        else
        {
            for (int sample = 0; sample < buffer.getNumSamples(); sample++)
            {
                channelData[sample] *= level;
            }
        }
    }
}
