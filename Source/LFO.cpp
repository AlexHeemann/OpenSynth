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
    switch (waveform)
    {
        case LFOWaveformSine:
            for (int sample = 0; sample < numSamples; ++sample)
            {
                currentPhase += phaseIncrement;
                if (currentPhase >= twoPi)
                {
                    currentPhase -= twoPi;
                }
            }
            break;
        default:
            currentPhase = 0;
            break;
    }
    
    currentValue = sin(currentPhase);
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
