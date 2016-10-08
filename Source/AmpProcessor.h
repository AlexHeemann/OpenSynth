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
#include "EnvelopeGenerator.h"

class AmpProcessor : public Processor
{
public:
    AmpProcessor();
    virtual ~AmpProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, AudioBuffer<float>& delayBuffer, int startSample, int numSamples)
    {
        processBuffer(outputBuffer, delayBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, AudioBuffer<double>& delayBuffer, int startSample, int numSamples)
    {
        processBuffer(outputBuffer, delayBuffer, startSample, numSamples);
    }
    
    void setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator);
    EnvelopeGenerator* getEnvelopeGenerator();
    AudioParameterFloat* level;
    
private:
    EnvelopeGenerator* envelopeGenerator;
    
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, int startSample, int numSamples);
};



#endif  // AMPPROCESSOR_H_INCLUDED
