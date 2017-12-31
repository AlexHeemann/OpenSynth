/*
  ==============================================================================

    DelayProcessor.cpp
    Created: 13 Nov 2016 12:36:14pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "DelayProcessor.h"
#include "DelayParameterContainer.h"

const String DelayProcessor::Constants::Identifiers::Delay = "delay";
const String DelayProcessor::Constants::Identifiers::Time = "time";
const String DelayProcessor::Constants::Identifiers::Feedback = "feedback";
const String DelayProcessor::Constants::Identifiers::Mix = "mix";

const String DelayProcessor::Constants::Names::Delay = "Delay";
const String DelayProcessor::Constants::Names::Time = "Time";
const String DelayProcessor::Constants::Names::Feedback = "Feedback";
const String DelayProcessor::Constants::Names::Mix = "Mix";

DelayProcessor::DelayProcessor(int ID,
                               ModulationMatrix* modulationMatrix,
                               AudioProcessorValueTreeState& audioProcessorValueTreeState,
                               IDManager& idManager,
                               int bufferSize,
                               int sampleRate) :
Processor(ID,
          modulationMatrix,
          audioProcessorValueTreeState,
          idManager,
          bufferSize),
maxDelayLength(5.0f),
isUsingDoublePrecision(true)
{
    delayTimeParameterID = idManager.getNewID();
    delayFeedbackParameterID = idManager.getNewID();
    delayMixParameterID = idManager.getNewID();
    
    setSampleRate(sampleRate);
    
    audioProcessorValueTreeState.createAndAddParameter(delayTimeParameterStringID(),
                                                       Constants::Names::Time,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.5,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(delayFeedbackParameterStringID(),
                                                       Constants::Names::Feedback,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.5,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(delayMixParameterStringID(),
                                                       Constants::Names::Mix,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.0,
                                                       nullptr,
                                                       nullptr);
}

DelayProcessor::~DelayProcessor() {}

String DelayProcessor::name() const
{
    return Constants::Names::Delay;
}

String DelayProcessor::stringIdentifier() const
{
    return Constants::Identifiers::Delay + String(ID);
}

String DelayProcessor::delayTimeParameterStringID() const
{
    stringIdentifier() + "_" + Constants::Identifiers::Time;
}

String DelayProcessor::delayFeedbackParameterStringID() const
{
    stringIdentifier() + "_" + Constants::Identifiers::Feedback;
}

String DelayProcessor::delayMixParameterStringID() const
{
    stringIdentifier() + "_" + Constants::Identifiers::Mix;
}

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
    const float feedback = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Feedback);
    const float mix = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Mix);
    const float time = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Time);
    setDelayTimeInSeconds(time);
    
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
//            if (localActiveChannel != channel)
//            {
//                delayChannelLevel = 1.0 - spread;
//            }
            
            const float dryMix = (1.0 - mix);
            const float wetMix = mix;
            channelData[i] = channelData[i] + delayData[delayPos] * feedback;
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
