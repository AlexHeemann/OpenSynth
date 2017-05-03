/*
  ==============================================================================

    LFOParameterContainer.h
    Created: 2 May 2017 9:02:42pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef LFOPARAMETERCONTAINER_H_INCLUDED
#define LFOPARAMETERCONTAINER_H_INCLUDED

#include "ParameterContainer.h"

class LFOParameterContainer : public ParameterContainer
{
public:
    LFOParameterContainer(AudioProcessor& processor) : processor(processor)
    {
        processor.addParameter(phaseOffsetParameter = new AudioParameterFloat("LFO_phaseOffset", "Phase Offset", 0.0f, 1.0f, 0.0f));
        processor.addParameter(frequencyParameter = new AudioParameterFloat("LFO_frequencyParameter", "Frequency", 0.0f, 20.0f, 5.0f));
    };
    
    virtual ~LFOParameterContainer() {};
    
    AudioParameterFloat* getPhaseOffsetParameter() const { return phaseOffsetParameter; }
    AudioParameterFloat* getFrequencyParameter() const { return frequencyParameter; }
    
    
private:
    AudioProcessor& processor;
    AudioParameterFloat* phaseOffsetParameter;
    AudioParameterFloat* frequencyParameter;
};


#endif // PARAMETERCONTAINER_H_INCLUDED

