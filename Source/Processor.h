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
#include "Module.h"

class Processor
{
public:
    Processor(ModulationMatrix *modulationMatrix) : modulationMatrix(modulationMatrix) {};
    virtual ~Processor() {};
    
    virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) = 0;
    virtual void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) = 0;
    
    virtual void setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator) { this->envelopeGenerator = envelopeGenerator; };
    virtual EnvelopeGenerator* getEnvelopeGenerator() const { return envelopeGenerator; };
    void setModulationMatrix(ModulationMatrix* modulationMatrix) { this->modulationMatrix = modulationMatrix; }
    ModulationMatrix* getModulationMatrix() { return modulationMatrix; }
    
protected:
    EnvelopeGenerator* envelopeGenerator;
    ModulationMatrix* modulationMatrix;
};


#endif  // PROCESSOR_H_INCLUDED
