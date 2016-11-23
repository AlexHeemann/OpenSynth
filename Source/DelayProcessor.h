/*
  ==============================================================================

    DelayProcessor.h
    Created: 13 Nov 2016 12:36:14pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef DELAYPROCESSOR_H_INCLUDED
#define DELAYPROCESSOR_H_INCLUDED

#include "Processor.h"

class DelayProcessor : public Processor
{
public:
    DelayProcessor();
    virtual ~DelayProcessor();
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
        processBuffer(outputBuffer, delayBufferFloat, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples)
    {
        processBuffer(outputBuffer, delayBufferDouble, startSample, numSamples);
    }
    
    void setIsUsingDoublePrecision(bool isUsingDoublePrecision);
    bool getIsUsingDoublePrecision() { return isUsingDoublePrecision; };
    void setDelayLengthInSeconds(float delayLength);
    float getDelayLengthInSeconds() { return delayLengthInSeconds; };
    void setDelayTimeInSeconds(float delayTime);
    int getDelayTimeInSeconds() { return delayTimeInSeconds; };
    void setSampleRate(int sampleRate);
    int getSampleRate() { return sampleRate; };
    void reset();
    
    AudioParameterFloat* delayLevel;
    AudioParameterFloat* delayMix;
    AudioParameterFloat* delayTime;
    AudioParameterFloat* delaySpread;
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, int startSample, int numSamples);
    void resizeDelayBuffers(int size);
    
    AudioBuffer<float> delayBufferFloat;
    AudioBuffer<double> delayBufferDouble;
    int sampleRate = 0;
    int delayPosition = 0;
    float delayLengthInSeconds = 0.0f;
    float delayTimeInSeconds = 0.0f;
    int delayTimeInSamples = 0;
    float maxDelayLength = 0.0f;
    bool isUsingDoublePrecision = false;
    int delayLengthInSamples = 0;
    int activeChannel = 0;
    bool shouldChangeActiveChannel = false;
};

#endif  // DELAYPROCESSOR_H_INCLUDED
