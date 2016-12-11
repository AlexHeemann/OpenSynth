/*
  ==============================================================================

    FilterParameterContainer.h
    Created: 4 Dec 2016 7:37:03pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef FILTERPARAMETERCONTAINER_H_INCLUDED
#define FILTERPARAMETERCONTAINER_H_INCLUDED

#include "ParameterContainer.h"

class FilterParameterContainer: public ParameterContainer
{
public:
    FilterParameterContainer(AudioProcessor& processor) : processor(processor)
    {
        processor.addParameter(filterFrequency = new AudioParameterFloat("filter_frequency", "Filter Frequency", 0.0f, 20000.0f, 10000.0f));
        filterFrequency->range.skew = 0.25;
        processor.addParameter(envelopeAmountFilter = new AudioParameterFloat("env_amount_filter", "Envelope Amount", 0.0f, 1.0f, 0.0f));
        processor.addParameter(filterResonance = new AudioParameterFloat("resonance", "Filter Resonance", 1.0f, 10.0f, 1.0f));
    }
    
    ~FilterParameterContainer() {}
    
    AudioParameterFloat* getEnvelopeAmountParameter() const { return envelopeAmountFilter; };
    AudioParameterFloat* getFilterFrequencyParameter() const { return filterFrequency; };
    AudioParameterFloat* getFilterResonanceParameter() const { return filterResonance; };
    
private:
    AudioProcessor& processor;
    
    AudioParameterFloat* envelopeAmountFilter;
    AudioParameterFloat* filterFrequency;
    AudioParameterFloat* filterResonance;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterParameterContainer)
};



#endif  // FILTERPARAMETERCONTAINER_H_INCLUDED
