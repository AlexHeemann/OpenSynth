/*
  ==============================================================================

    DelayProcessor.cpp
    Created: 13 Nov 2016 12:36:14pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "DelayProcessor.h"
#include "DelayParameterContainer.h"

DelayProcessor::DelayProcessor(ModulationMatrix* modulationMatrix, int bufferSize) : Processor(modulationMatrix, bufferSize), maxDelayLength(5.0f), isUsingDoublePrecision(true)
{
}

DelayProcessor::~DelayProcessor() {}

void DelayProcessor::setIsUsingDoublePrecision(bool isUsingDoublePrecision)
{
    this->isUsingDoublePrecision = isUsingDoublePrecision;
}

void DelayProcessor::setDelayLengthInSeconds(float delayLength)
{
    this->delayLengthInSeconds = delayLength;
    resizeDelayBuffers(delayLength * sampleRate);
}

void DelayProcessor::setDelayTimeInSeconds(float delayTime)
{
    this->delayTimeInSeconds = delayTime;
    this->delayTimeInSamples = delayTime * sampleRate;
}

void DelayProcessor::setSampleRate(int sampleRate)
{
    this->sampleRate = sampleRate;
    resizeDelayBuffers(maxDelayLength * sampleRate);
    this->delayTimeInSamples = delayTimeInSeconds * sampleRate;
}

void DelayProcessor::resizeDelayBuffers(int size)
{
    if (size == delayLengthInSamples)
    {
        return;
    }
    delayLengthInSamples = size;
    if (isUsingDoublePrecision)
    {
        this->delayBufferDouble.setSize(2, size);
        this->delayBufferFloat.setSize(1, 1);
    }
    else
    {
        this->delayBufferFloat.setSize(2, size);
        this->delayBufferDouble.setSize(1, 1);
    }
    this->delayBufferFloat.clear();
    this->delayBufferDouble.clear();
    delayPosition = 0;
}

void DelayProcessor::reset()
{
    delayPosition = 0;
    delayBufferFloat.clear();
    delayBufferDouble.clear();
}

template <typename FloatType>
void DelayProcessor::processBuffer(AudioBuffer<FloatType> &buffer, AudioBuffer<FloatType> &delayBuffer, int startSample, int numSamples)
{
    const float localDelayLevel = parameterContainer->getDelayFeedbackParameter()->get();
    const float localMix = parameterContainer->getDelayMixParameter()->get();
    const float spread = parameterContainer->getDelaySpreadParameter()->get();
    setDelayTimeInSeconds(parameterContainer->getDelayTimeParameter()->get());
    
    int delayPos = 0;
    int localActiveChannel = activeChannel;
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        FloatType* const channelData = buffer.getWritePointer(channel);
        FloatType* const delayData = delayBuffer.getWritePointer(jmin(channel, delayBuffer.getNumChannels() - 1));
        delayPos = delayPosition;
        localActiveChannel = activeChannel;
        
        for (int i = startSample; i < numSamples; ++i)
        {
            float delayChannelLevel = 1.0;
            if (localActiveChannel != channel)
            {
                delayChannelLevel = 1.0 - spread;
            }
            
            //const float dryMix = (1.0 - localMix);
            //const float wetMix = localMix;
            channelData[i] = channelData[i] + delayData[delayPos] * localDelayLevel;
            delayData[delayPos] = channelData[i] * delayChannelLevel;
            
            delayPos++;
            if (delayPos >= delayTimeInSamples || delayPos >= delayBuffer.getNumSamples())
            {
                delayPos = 0;
                localActiveChannel = (localActiveChannel + 1) % buffer.getNumChannels();
            }
        }
    }
    
    activeChannel = localActiveChannel;
    delayPosition = delayPos;
    
    if (output != nullptr)
    {
        output->renderNextBlock(buffer, startSample, numSamples);
    }
}
