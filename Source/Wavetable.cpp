/*
  ==============================================================================

    Wavetable.cpp
    Created: 20 Sep 2016 7:42:28pm
    Author:  Alex

  ==============================================================================
*/

#include "Wavetable.h"

Wavetable::Wavetable(float lowestFrequency, int tableSize, int sampleRate) : lowestFrequency(lowestFrequency), tableSize(tableSize), sampleRate(sampleRate)
{
	// Initialize subtables
	subtables = (float**)calloc(9, sizeof(float*));
	for (int i = 0; i < 9; i++)
	{
		subtables[i] = (float*)calloc(tableSize, sizeof(float));
	}
}

Wavetable::~Wavetable()
{
	for (int i = 0; i < 9; i++)
	{
		free(subtables[i]);
	}
	free(subtables);
}

float* Wavetable::getSubtableForFrequency(float frequency)
{
	int index = 8;
	int highestFrequency = lowestFrequency * (1 << index);
	if (frequency < lowestFrequency)
	{
		index = 1;
	}
	else
	{
		while (frequency < highestFrequency)
		{
			highestFrequency = lowestFrequency * (1 << --index);
		}
	}
	
	return subtables[index];
}

int Wavetable::getTableSize()
{
    return tableSize;
}
