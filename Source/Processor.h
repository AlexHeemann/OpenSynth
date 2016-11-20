/*
  ==============================================================================

    Processor.h
    Created: 6 Oct 2016 2:34:51pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeGenerator.h"

class Processor
{
public:
    Processor() {};
    virtual ~Processor() {};
    
    virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) = 0;
    virtual void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) = 0;
    
    virtual void setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator) { this->envelopeGenerator = envelopeGenerator; };
    virtual EnvelopeGenerator* getEnvelopeGenerator() const { return envelopeGenerator; };
    
protected:
    EnvelopeGenerator* envelopeGenerator;
};


#endif  // PROCESSOR_H_INCLUDED
