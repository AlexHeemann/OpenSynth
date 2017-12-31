/*
  ==============================================================================

    LFO.cpp
    Created: 24 Apr 2017 9:55:03am
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "LFO.h"
#include "ModulationMatrix.h"
#include "LFOParameterContainer.h"

const String LFO::Constants::Identifiers::LFO = "lfo";
const String LFO::Constants::Identifiers::Frequency = "frequency";
const String LFO::Constants::Identifiers::PhaseOffset = "phase_offset";
const String LFO::Constants::Identifiers::Waveform = "waveform";

const String LFO::Constants::Names::LFO = "LFO";
const String LFO::Constants::Names::Frequency = "Frequency";
const String LFO::Constants::Names::PhaseOffset = "Phase";
const String LFO::Constants::Names::Waveform = "Waveform";

LFO::LFO(int ID,
         ModulationMatrix *modulationMatrix,
         AudioProcessorValueTreeState& audioProcessorValueTreeState,
         IDManager& idManager,
         int sampleRate) :
Module(ID,
modulationMatrix,
       audioProcessorValueTreeState,
       idManager)
{
    setSampleRate(sampleRate);
    frequencyParameterID = idManager.getNewID();
    phaseOffsetParameterID = idManager.getNewID();
    waveformParameterID = idManager.getNewID();
    
    audioProcessorValueTreeState.createAndAddParameter(frequencyParameterStringID(),
                                                       Constants::Names::Frequency,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 20.0f),
                                                       5.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(phaseOffsetParameterStringID(),
                                                       Constants::Names::PhaseOffset,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(waveformParameterStringID(),
                                                       Constants::Names::Waveform,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 3.0f, 1.0f),
                                                       0.0f,
                                                       nullptr,
                                                       nullptr);
}

String LFO::stringIdentifier() const
{
    return LFO::Constants::Identifiers::LFO + String(ID);
}

String LFO::frequencyParameterStringID()
{
    return stringIdentifier() + "_" + Constants::Identifiers::Frequency;
}

String LFO::phaseOffsetParameterStringID()
{
    return stringIdentifier() + "_" + Constants::Identifiers::PhaseOffset;
}

String LFO::waveformParameterStringID()
{
    return stringIdentifier() + "_" + Constants::Identifiers::Waveform;
}

void LFO::calculatePhaseIncrement()
{
    double modulation = modulationMatrix->getValueForDestinationID(frequencyParameterID);
    float frequency = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Frequency);
    NormalisableRange<float> frequencyRange = audioProcessorValueTreeState.getParameterRange(Constants::Identifiers::Frequency);
    
    float newKnobValue = std::fmin(1.0f, frequencyRange.convertTo0to1(frequency) + modulation);
    float newFrequency = std::fmax(0.0f, std::fmin(frequencyRange.end, frequencyRange.convertFrom0to1(newKnobValue)));
    
    phaseIncrement = newFrequency * frqRad;
}

void LFO::reset()
{
    currentPhase = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::PhaseOffset) * 2.0 * double_Pi;
}

void LFO::calculateModulation(int numSamples)
{
    calculatePhaseIncrement();
    double twoPi = 2.0 * double_Pi;
    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        currentPhase += phaseIncrement;
        if (currentPhase >= twoPi)
        {
            currentPhase -= twoPi;
        }
    }
    
    switch (Waveform(*audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Waveform)).type)
    {
        case WaveformSine:
            currentValue = sin(currentPhase);
            break;
        case WaveformSawtooth:
            currentValue = (((currentPhase / twoPi) * 2.0) - 1) * -1;
            break;
        case WaveformSquare:
            if (currentPhase > twoPi / 2.0)
            {
                currentValue = -1;
            }
            else
            {
                currentValue = 1;
            }
            break;
        case WaveformTriangle:
        {
            currentValue = (currentPhase < double_Pi ? currentPhase / double_Pi : 1.0 - (currentPhase - double_Pi) / double_Pi) * 2.0 - 1.0;
            break;
        }
        default:
            currentValue = 0;
            break;
    }
}
