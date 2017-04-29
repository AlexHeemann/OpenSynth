/*
  ==============================================================================

    AmpProcessor.h
    Created: 6 Oct 2016 2:33:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef AMPPROCESSOR_H_INCLUDED
#define AMPPROCESSOR_H_INCLUDED

#include "Processor.h"

class AmpProcessor : public Processor
{
public:
    AmpProcessor(ModulationMatrix* modulationMatrix);
    virtual ~AmpProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    
    AudioParameterFloat* level;
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
};



#endif  // AMPPROCESSOR_H_INCLUDED
