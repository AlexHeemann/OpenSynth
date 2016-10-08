/*
  ==============================================================================

    FilterProcessor.cpp
    Created: 8 Oct 2016 2:44:22pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "FilterProcessor.h"

FilterProcessor::FilterProcessor()
{
    initialiseLowPassFilter(20000);
}

template <typename FloatType>
void FilterProcessor::processBuffer(AudioBuffer<FloatType> &buffer, AudioBuffer<FloatType>& delayBuffer, int startSample, int numSamples)
{
    bool isModulated = envelopeGenerator != nullptr && envelopeGenerator->envelopeBuffer.size() >= numSamples && numSamples > 0;
    float filterModulation = isModulated ? envelopeGenerator->envelopeBuffer[0] : 1.0;
    
    for (int filterIdx = 0; filterIdx < filters.size(); filterIdx++)
    {
        filters[filterIdx].setParam(Dsp::ParamID::idFrequency, std::fmax(0.0f, std::fmin(frequency->range.end, frequency->get() + envelopeAmount->get() * filterModulation)));
    }
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        FloatType* writePointer = buffer.getWritePointer(channel);
        FloatType* audioData[1];
        audioData[0] = writePointer;
        filters[channel].process(numSamples, audioData);
    }
}

void FilterProcessor::initialiseLowPassFilter(double frequency)
{
    filters.clear();
    for (int filter = 0; filter < 2; filter++)
    {
        Dsp::SmoothedFilterDesign <Dsp::RBJ::Design::LowPass, 1> f(1024);
        Dsp::Params params;
        params[0] = 44100; // sample rate
        params[1] = 500; // cutoff frequency
        params[2] = 1.25; // Q
        f.setParams(params);
        filters.push_back(f);
    }
};
