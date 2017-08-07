/*
  ==============================================================================

    FilterProcessor.cpp
    Created: 8 Oct 2016 2:44:22pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "FilterProcessor.h"
#include "FilterParameterContainer.h"
#include "ModulationMatrix.h"
#include "PluginProcessor.h"

FilterProcessor::FilterProcessor(ModulationMatrix* modulationMatrix, int bufferSize) : Processor(modulationMatrix, bufferSize)
{
    initialiseLowPassFilter(20000);
    initialiseHighPassFilter(20000);
    initialiseBandPassFilter(20000);
    initialiseAllPassFilter(20000);
}

void FilterProcessor::renderNextBlock()
{
    Processor::aggregateInputs(audioBuffer);
    renderNextBlock(audioBuffer, 0, audioBuffer.getNumSamples());
}

template <typename FloatType, typename DspFilterType>
void FilterProcessor::processBufferWithFilter(AudioBuffer<FloatType> &buffer, int startSample, int numSamples, std::vector<DspFilterType>& filters)
{
    float filterModulation = modulationMatrix->getValueForDestinationID(ParameterIDFilterCutoff);
    AudioParameterFloat* frequency = parameterContainer->getFilterFrequencyParameter();
    AudioParameterFloat* resonance = parameterContainer->getFilterResonanceParameter();
    
    for (int filterIdx = 0; filterIdx < filters.size(); filterIdx++)
    {
        float newKnobValue = std::min(1.0f, frequency->range.convertTo0to1(frequency->get()) + filterModulation);
        filters[filterIdx].setParam(Dsp::ParamID::idFrequency, std::fmax(0.0f, std::fmin(frequency->range.end, frequency->range.convertFrom0to1(newKnobValue))));
        filters[filterIdx].setParam(Dsp::ParamID::idQ, resonance->get());
    }
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        FloatType* writePointer = buffer.getWritePointer(channel);
        FloatType* audioData[1];
        audioData[0] = writePointer;
        filters[channel].process(numSamples, audioData);
    }
}

template <typename FloatType>
void FilterProcessor::processBuffer(AudioBuffer<FloatType> &buffer, int startSample, int numSamples)
{
    switch (activeFilter)
    {
        case LowPass:
            processBufferWithFilter(buffer, startSample, numSamples, lowPassFilters);
            break;
        case HighPass:
            processBufferWithFilter(buffer, startSample, numSamples, highPassFilters);
            break;
        case BandPass:
            processBufferWithFilter(buffer, startSample, numSamples, bandPassFilters);
            break;
        case AllPass:
            processBufferWithFilter(buffer, startSample, numSamples, allPassFilters);
            break;
    }
}

void FilterProcessor::resetFilter()
{
    initialiseLowPassFilter(parameterContainer->getFilterFrequencyParameter()->get());
    initialiseHighPassFilter(parameterContainer->getFilterFrequencyParameter()->get());
    initialiseBandPassFilter(parameterContainer->getFilterFrequencyParameter()->get());
    initialiseAllPassFilter(parameterContainer->getFilterFrequencyParameter()->get());
}

void FilterProcessor::initialiseLowPassFilter(double frequency)
{
    lowPassFilters.clear();
    for (int filter = 0; filter < 2; filter++)
    {
        Dsp::SmoothedFilterDesign <Dsp::RBJ::Design::LowPass, 1> f(1024);
        Dsp::Params params;
        params[0] = 44100; // sample rate
        params[1] = frequency; // cutoff frequency
        params[2] = 1.0; // Q
        f.setParams(params);
        lowPassFilters.push_back(f);
    }
};

void FilterProcessor::initialiseHighPassFilter(double frequency)
{
    highPassFilters.clear();
    for (int filter = 0; filter < 2; filter++)
    {
        Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::HighPass, 1> f(1024);
        Dsp::Params params;
        params[0] = 44100; // sample rate
        params[1] = frequency; // cutoff frequency
        params[2] = 1.0; // Q
        f.setParams(params);
        highPassFilters.push_back(f);
    }
}

void FilterProcessor::initialiseBandPassFilter(double frequency)
{
    bandPassFilters.clear();
    for (int filter = 0; filter < 2; filter++)
    {
        Dsp::SmoothedFilterDesign <Dsp::RBJ::Design::BandPass1, 1> f(1024);
        Dsp::Params params;
        params[0] = 44100; // sample rate
        params[1] = frequency; // cutoff frequency
        params[2] = 1.0; // Q
        f.setParams(params);
        bandPassFilters.push_back(f);
    }
};

void FilterProcessor::initialiseAllPassFilter(double frequency)
{
    allPassFilters.clear();
    for (int filter = 0; filter < 2; filter++)
    {
        Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::AllPass, 1> f(1024);
        Dsp::Params params;
        params[0] = 44100; // sample rate
        params[1] = frequency; // cutoff frequency
        params[2] = 1.0; // Q
        f.setParams(params);
        allPassFilters.push_back(f);
    }
}

void FilterProcessor::setActiveFilter(FilterType activeFilter)
{
    this->activeFilter = activeFilter;
}

void FilterProcessor::setParameterContainer(FilterParameterContainer* parameterContainer)
{
    this->parameterContainer = parameterContainer;
}

