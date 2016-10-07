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
    level = new AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.9f);
}

void AmpProcessor::setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator)
{
    this->envelopeGenerator = envelopeGenerator;
}

EnvelopeGenerator* AmpProcessor::getEnvelopeGenerator()
{
    return envelopeGenerator;
}

template <typename FloatType>
void AmpProcessor::processBuffer(AudioBuffer<FloatType> &buffer, juce::MidiBuffer &midiMessages, AudioBuffer<FloatType> &delayBuffer)
{
    bool isModulated = envelopeGenerator != nullptr;
    if (isModulated)
    {
        envelopeGenerator->calculateEnvelopeBuffer(buffer.getNumSamples());
    }
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        FloatType* const channelData = buffer.getWritePointer(channel);
        isModulated = isModulated && envelopeGenerator->envelopeBuffer.size() >= buffer.getNumSamples();
        const float localLevel = level->get();
        if (isModulated)
        {
            std::vector<double> envelopeBuffer = envelopeGenerator->envelopeBuffer;
            for (int sample = 0; sample < buffer.getNumSamples(); sample++)
            {
                channelData[sample] *= localLevel * envelopeBuffer[sample];
            }
        }
        else
        {
            for (int sample = 0; sample < buffer.getNumSamples(); sample++)
            {
                channelData[sample] *= localLevel;
            }
        }
    }
}
