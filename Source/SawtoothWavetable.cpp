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
    if (sampleRate <= 0)
    {
        return;
    }
    currentAngle = 0.0;
    frqRad = twoPi / sampleRate;
    
    frequency = 1 / ((float)tableSize / (float)sampleRate);
    float phaseIncrement_0 = frqRad * frequency;
    
	int numPartials = 368;
    // Lanczos sigma factor to eliminate much of the ripple
    float sigmaK = double_Pi / numPartials;
	for (int index = 0; index < 9; index++)
    {
        for (int partialIdx = 0; partialIdx < numPartials; partialIdx++)
        {
            float partialMultiple = partialIdx + 1;
            float sigmaN = partialMultiple * sigmaK;
            float sigma = std::sin(sigmaN) / sigmaN;
            float partialAmplitude = (1.0 / partialMultiple) * sigma;
            float phaseIncrement = phaseIncrement_0 * partialMultiple;
            float phase = 0.0;
            
            for (int sampleIdx = 0; sampleIdx < tableSize; sampleIdx++)
            {
                double value = std::sin(phase) * partialAmplitude;
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
