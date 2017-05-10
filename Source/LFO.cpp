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
    phaseIncrement = parameterContainer->getFrequencyParameter()->get() * frqRad;
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
    
    modulationMatrix->setValueForSourceID(ID, currentValue);
}

void LFO::addTarget(int targetID)
{
    modulationMatrix->addRow(ID, targetID);
    targets.insert(targetID);
}

void LFO::removeTarget(int targetID)
{
    modulationMatrix->removeRow(ID, targetID);
    targets.erase(targetID);
}
