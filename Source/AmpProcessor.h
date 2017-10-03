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

class AmpParameterContainer;

class AmpProcessor : public Processor
{
public:
    AmpProcessor(ModulationMatrix* modulationMatrix, int bufferSize);
    virtual ~AmpProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock() override {};
    void reset() override {};
    
    void setParameterContainer(AmpParameterContainer* parameterContainer) { this->parameterContainer = parameterContainer; }
    AmpParameterContainer* getParameterContainer() const { return parameterContainer; }
    
private:
    AmpParameterContainer* parameterContainer;
    
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
};



#endif  // AMPPROCESSOR_H_INCLUDED
