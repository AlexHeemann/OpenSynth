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

void LFO::calculatePhaseIncrement()
{
    double modulation = modulationMatrix->getValueForDestinationID(ParameterIDLFO1Frequency);
    AudioParameterFloat* frequencyParameter = parameterContainer->getFrequencyParameter();
    float newKnobValue = std::fmin(1.0f, frequencyParameter->range.convertTo0to1(frequencyParameter->get()) + modulation);
    float newFrequency = std::fmax(0.0f, std::fmin(frequencyParameter->range.end, frequencyParameter->range.convertFrom0to1(newKnobValue)));
    
    phaseIncrement = newFrequency * frqRad;
}

void LFO::reset()
{
    currentPhase = parameterContainer->getPhaseOffsetParameter()->get() * 2.0 * double_Pi;
}

void LFO::oscillate(int numSamples)
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
    
    switch (parameterContainer->getWaveformParameter()->getIndex())
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
