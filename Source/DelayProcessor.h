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
    
    struct Constants
    {
        struct Identifiers
        {
            static const String Delay;
            static const String Time;
            static const String Feedback;
            static const String Mix;
        };
        struct Names
        {
            static const String Delay;
            static const String Time;
            static const String Feedback;
            static const String Mix;
        };
    };
    
    DelayProcessor(int ID,
                   ModulationMatrix* modulationMatrix,
                   AudioProcessorValueTreeState& audioProcessorValueTreeState,
                   IDManager& idManager,
                   int bufferSize,
                   int sampleRate);
    virtual ~DelayProcessor();
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, delayBufferFloat, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, delayBufferDouble, startSample, numSamples);
    }
    
    void renderNextBlock() override
    {
        
    }
    
    void setIsUsingDoublePrecision(bool isUsingDoublePrecision);
    const bool getIsUsingDoublePrecision() const { return isUsingDoublePrecision; };
    void setDelayLengthInSeconds(float delayLength);
    const float getDelayLengthInSeconds() const { return delayLengthInSeconds; };
    void setDelayTimeInSeconds(float delayTime);
    const int getDelayTimeInSeconds() const { return delayTimeInSeconds; };
    void setSampleRate(int sampleRate) override;
    const int getSampleRate() const { return sampleRate; };
    void reset() override;
    String name() const override;
    
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
    
    // Parameters
    int delayTimeParameterID;
    int delayFeedbackParameterID;
    int delayMixParameterID;
    
    String stringIdentifier() const override;
    
    String delayTimeParameterStringID() const;
    String delayFeedbackParameterStringID() const;
    String delayMixParameterStringID() const;
};

#endif  // DELAYPROCESSOR_H_INCLUDED
