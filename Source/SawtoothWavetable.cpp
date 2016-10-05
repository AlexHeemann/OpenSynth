/*
  ==============================================================================

    SawtoothWavetable.cpp
    Created: 20 Sep 2016 7:43:12pm
    Author:  Alex

  ==============================================================================
*/

#include "SawtoothWavetable.h"

SawtoothWavetable::SawtoothWavetable(float lowestFrequency, int tableSize, int sampleRate) :
	Wavetable(lowestFrequency, tableSize, sampleRate)
{
    calculateSubtables();
}

SawtoothWavetable::~SawtoothWavetable()
{

}

void SawtoothWavetable::calculateSubtables()
{
    currentAngle = 0.0;
    frqRad = twoPi / sampleRate;
    
    frequency = 1 / ((float)tableSize / (float)sampleRate);
    float phaseIncrement_0 = frqRad * frequency;
    
	int numPartials = 368;
	for (int index = 0; index < 8; index++)
    {
        for (int partialIdx = 0; partialIdx < numPartials; partialIdx++)
        {
            float partialMultiple = partialIdx + 1;
            float partialAmplitude = 1.0 / partialMultiple;
            float phaseIncrement = phaseIncrement_0 * partialMultiple;
            float phase = 0.0;
            
            // Calculate scale to normalize amplitudes
            for (int n = 0; n < tableSize; n++)
            {
                double value = 0.0;
                value += std::sin(phase) * partialAmplitude;
                if ((phase += phaseIncrement) >= twoPi)
                {
                    phase -= twoPi;
                }

                scale = value > scale ? value : scale;
            }
            
            for (int sampleIdx = 0; sampleIdx < tableSize; sampleIdx++)
            {
                double value = 0.0;
                value += std::sin(phase) * partialAmplitude;
                if ((phase += phaseIncrement) >= twoPi)
                {
                    phase -= twoPi;
                }

                subtables[index][sampleIdx] = (value / scale);
            }
        }
        
        numPartials /= 2;
	}
}
