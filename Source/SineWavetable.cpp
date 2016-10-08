/*
  ==============================================================================

    SineWavetable.cpp
    Created: 8 Oct 2016 7:12:45pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "SineWavetable.h"

SineWavetable::SineWavetable(float lowestFrequency, int tableSize, int sampleRate) :
Wavetable(lowestFrequency, tableSize, sampleRate)
{
    calculateSubtables();
}

SineWavetable::~SineWavetable()
{
    
}

void SineWavetable::calculateSubtables()
{
    if (sampleRate <= 0)
    {
        return;
    }
    currentAngle = 0.0;
    frqRad = twoPi / sampleRate;
    
    frequency = 1 / ((float)tableSize / (float)sampleRate);
    float phaseIncrement = frqRad * frequency;
    
    int numPartials = 1;
    for (int index = 0; index < 9; index++)
    {
        for (int partialIdx = 0; partialIdx < numPartials; partialIdx++)
        {
            float phase = 0.0;
            for (int sampleIdx = 0; sampleIdx < tableSize; sampleIdx++)
            {
                double value = std::sin(phase);
                if ((phase += phaseIncrement) >= twoPi)
                {
                    phase -= twoPi;
                }
                
                subtables[index][sampleIdx] += value;
            }
        }
        // Calculate scale to normalize amplitudes
        scale = 1.0;
        for (int sampleIdx = 0; sampleIdx < tableSize; sampleIdx++)
        {
            scale = subtables[index][sampleIdx] > scale ? subtables[index][sampleIdx] : scale;
        }
        for (int sampleIdx = 0; sampleIdx < tableSize; sampleIdx++)
        {
            subtables[index][sampleIdx] = subtables[index][sampleIdx] / scale;
        }
        
        numPartials = std::max(1, numPartials / 2);
    }
}
