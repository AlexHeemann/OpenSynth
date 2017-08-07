/*
  ==============================================================================

    OscillatorProcessor.h
    Created: 7 Aug 2017 6:58:17pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include "Processor.h"

class OscillatorParameterContainer;

class OscillatorProcessor : public Processor
{
public:
    OscillatorProcessor(ModulationMatrix* modulationMatrix, int bufferSize);
    virtual ~OscillatorProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock() override {};
    
    void setParameterContainer(OscillatorParameterContainer* parameterContainer) { this->parameterContainer = parameterContainer; };
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
    
    OscillatorParameterContainer* parameterContainer;
};
