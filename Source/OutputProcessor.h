/*
  ==============================================================================

    OutputProcessor.h
    Created: 7 Aug 2017 5:32:24pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include "Processor.h"

class OutputProcessor: public Processor
{
public:
    OutputProcessor(ModulationMatrix *modulationMatrix, int bufferSize);
    virtual ~OutputProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override;
    
private:
    
};
