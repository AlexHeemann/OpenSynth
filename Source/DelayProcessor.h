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

class DelayParameterContainer;

class DelayProcessor : public Processor
{
public:
    DelayProcessor(ModulationMatrix* modulationMatrix, int bufferSize);
    virtual ~DelayProcessor();
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, delayBufferFloat, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, delayBufferDouble, startSample, numSamples);
    }
    
    void setIsUsingDoublePrecision(bool isUsingDoublePrecision);
    const bool getIsUsingDoublePrecision() const { return isUsingDoublePrecision; };
    void setDelayLengthInSeconds(float delayLength);
    const float getDelayLengthInSeconds() const { return delayLengthInSeconds; };
    void setDelayTimeInSeconds(float delayTime);
    const int getDelayTimeInSeconds() const { return delayTimeInSeconds; };
    void setSampleRate(int sampleRate);
    const int getSampleRate() const { return sampleRate; };
    void reset() override;
    void setParameterContainer(DelayParameterContainer* parameterContainer) { this->parameterContainer = parameterContainer; };
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, int startSample, int numSamples);
    void resizeDelayBuffers(int size);
    
    DelayParameterContainer* parameterContainer;
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
