/*
  ==============================================================================

    ReverbProcessor.h
    Created: 24 Nov 2016 8:05:38pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef REVERBPROCESSOR_H_INCLUDED
#define REVERBPROCESSOR_H_INCLUDED

#include "Processor.h"
#include "ReverbDouble.h"

class ReverbParameterContainer;

class ReverbProcessor : public Processor
{
public:
    ReverbProcessor(ModulationMatrix* modulationMatrix, int bufferSize);
    virtual ~ReverbProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    
    void setSampleRate(const int sampleRate);
    const int getSampleRate() const { return sampleRate; };
    void reset() override;
    void setReverbParameterContainer(ReverbParameterContainer* reverbParameterContainer)
    {
        this->reverbParameterContainer = reverbParameterContainer;
    };
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
    
    int sampleRate = 0;
    
    ReverbDouble reverb;
    ReverbDouble::Parameters reverbParameters;
    ReverbParameterContainer* reverbParameterContainer;
};

#endif  // REVERBPROCESSOR_H_INCLUDED
