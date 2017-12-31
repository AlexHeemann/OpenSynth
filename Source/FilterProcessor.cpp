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

const String FilterProcessor::Constants::Identifiers::Filter = "filter";
const String FilterProcessor::Constants::Identifiers::Frequency = "frequency";
const String FilterProcessor::Constants::Identifiers::Resonance = "resonance";
const String FilterProcessor::Constants::Identifiers::FilterType = "filter_type";

const String FilterProcessor::Constants::Names::Filter = "Filter";
const String FilterProcessor::Constants::Names::Frequency = "Frequency";
const String FilterProcessor::Constants::Names::Resonance = "Resonance";
const String FilterProcessor::Constants::Names::FilterType = "Filter Type";

FilterProcessor::FilterProcessor(int ID,
                                 ModulationMatrix* modulationMatrix,
                                 AudioProcessorValueTreeState& audioProcessorValueTreeState,
                                 IDManager& idManager,
                                 int bufferSize) :
Processor(ID,
          modulationMatrix,
          audioProcessorValueTreeState,
          idManager,
          bufferSize)
{
    initialiseLowPassFilter(20000);
    initialiseHighPassFilter(20000);
    initialiseBandPassFilter(20000);
    initialiseAllPassFilter(20000);
    
    filterFrequencyParameterID = idManager.getNewID();
    filterResonanceParameterID = idManager.getNewID();
    audioProcessorValueTreeState.createAndAddParameter(filterFrequencyParameterStringID(),
                                                       Constants::Names::Frequency,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 20000.0f, 0.0f, 0.25f),
                                                       10000.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(filterResonanceParameterStringID(),
                                                       Constants::Names::Frequency,
                                                       String(),
                                                       NormalisableRange<float>(1.0f, 5.0f),
                                                       1.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(filterTypeParameterStringID(),
                                                       Constants::Names::FilterType,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 3.0f, 1.0f),
                                                       0.0f,
                                                       nullptr,
                                                       nullptr);
}

String FilterProcessor::stringIdentifier() const
{
    return Constants::Identifiers::Filter + String(ID);
}

String FilterProcessor::filterFrequencyParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Frequency;
}

String FilterProcessor::filterResonanceParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Resonance;
}

String FilterProcessor::filterTypeParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::FilterType;
}

String FilterProcessor::name() const
{
    return Constants::Names::Filter;
}

void FilterProcessor::renderNextBlock()
{
    Processor::aggregateInputs(audioBuffer);
    renderNextBlock(audioBuffer, 0, audioBuffer.getNumSamples());
}

template <typename FloatType, typename DspFilterType>
void FilterProcessor::processBufferWithFilter(AudioBuffer<FloatType> &buffer, int startSample, int numSamples, std::vector<DspFilterType>& filters)
{
    float filterModulation = modulationMatrix->getValueForDestinationID(filterFrequencyParameterID);
    float frequency = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Frequency);
    float resonance = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Resonance);
    NormalisableRange<float> frequencyRange = audioProcessorValueTreeState.getParameterRange(Constants::Identifiers::Frequency);
    NormalisableRange<float> resonanceRange = audioProcessorValueTreeState.getParameterRange(Constants::Identifiers::Resonance);
    
    for (int filterIdx = 0; filterIdx < filters.size(); filterIdx++)
    {
        float newKnobValue = std::min(1.0f, frequencyRange.convertTo0to1(frequency) + filterModulation);
        filters[filterIdx].setParam(Dsp::ParamID::idFrequency, std::fmax(0.0f,
                                                                         std::fmin(frequencyRange.end,
                                                                                   frequencyRange.convertFrom0to1(newKnobValue))));
        filters[filterIdx].setParam(Dsp::ParamID::idQ, resonance);
    }
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        FloatType* writePointer = buffer.getWritePointer(channel);
        FloatType* audioData[1];
        audioData[0] = writePointer;
        filters[channel].process(numSamples, audioData);
    }
    
    if (output != nullptr)
    {
        output->renderNextBlock(buffer, startSample, numSamples);
    }
}

template <typename FloatType>
void FilterProcessor::processBuffer(AudioBuffer<FloatType> &buffer, int startSample, int numSamples)
{
    float filterType = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::FilterType);
    if (filterType < 0.5)
    {
        // Low Pass
        processBufferWithFilter(buffer, startSample, numSamples, lowPassFilters);
    }
    else if (filterType < 1.5)
    {
        // High Pass
        processBufferWithFilter(buffer, startSample, numSamples, highPassFilters);
    }
    else if (filterType < 2.5)
    {
        // Band Pass
        processBufferWithFilter(buffer, startSample, numSamples, bandPassFilters);
    }
    else if (filterType < 3.5)
    {
        // All Pass
        processBufferWithFilter(buffer, startSample, numSamples, allPassFilters);
    }
}

void FilterProcessor::reset()
{
    float frequency = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Frequency);
    initialiseLowPassFilter(frequency);
    initialiseHighPassFilter(frequency);
    initialiseBandPassFilter(frequency);
    initialiseAllPassFilter(frequency);
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
