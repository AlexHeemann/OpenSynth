/*
  ==============================================================================

    Wavetable.cpp
    Created: 20 Sep 2016 7:42:28pm
    Author:  Alex

  ==============================================================================
*/

#include "Wavetable.h"

Wavetable::Wavetable(float lowestFrequency, int tableSize)
{
	lowestFrequency = lowestFrequency;
	tableSize = tableSize;

	// Initialize subtables
	subtables = (float**)malloc(sizeof(float*) * 8);
	for (int i = 0; i < 8; i++)
	{
		subtables[i] = (float*)malloc(sizeof(float) * tableSize);
	}

	calculateSubtables();
}

Wavetable::~Wavetable()
{
	for (int i = 0; i < 8; i++)
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
	
	return subtables[index - 1];
}
