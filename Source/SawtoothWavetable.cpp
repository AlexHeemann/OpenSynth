/*
  ==============================================================================

    SawtoothWavetable.cpp
    Created: 20 Sep 2016 7:43:12pm
    Author:  Alex

  ==============================================================================
*/

#include "SawtoothWavetable.h"

SawtoothWavetable::SawtoothWavetable(float lowestFrequency, int tableSize) :
	Wavetable(lowestFrequency, tableSize)
{

}

SawtoothWavetable::~SawtoothWavetable()
{

}

void SawtoothWavetable::calculateSubtables()
{
	int numPartials = 368;
	for (int index = 0; index < 8; index++)
	{

	}
}