/*
  ==============================================================================

    FilterProcessor.h
    Created: 8 Oct 2016 2:44:22pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef FILTERPROCESSOR_H_INCLUDED
#define FILTERPROCESSOR_H_INCLUDED

#include "Processor.h"
#include "DspFilters/Dsp.h"

class FilterProcessor : public Processor
{
public:
    FilterProcessor();
    virtual ~FilterProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, AudioBuffer<float>& delayBuffer, int startSample, int numSamples)
    {
        processBuffer(outputBuffer, delayBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, AudioBuffer<double>& delayBuffer, int startSample, int numSamples)
    {
        processBuffer(outputBuffer, delayBuffer, startSample, numSamples);
    }
    
    AudioParameterFloat* frequency;
    AudioParameterFloat* envelopeAmount;
    AudioParameterFloat* resonance;
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, int startSample, int numSamples);
    void initialiseLowPassFilter(double frequency);
    
    // Contains filters for left and right channel
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::LowPass, 1>> filters;
};


#endif  // FILTERPROCESSOR_H_INCLUDED
