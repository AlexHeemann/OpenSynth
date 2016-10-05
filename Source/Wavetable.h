/*
  ==============================================================================

    Wavetable.h
    Created: 20 Sep 2016 7:42:28pm
    Author:  Alex

  ==============================================================================
*/

#ifndef WAVETABLE_H_INCLUDED
#define WAVETABLE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Wavetable
{
public:
	Wavetable(float lowestFrequency, int tableSize);
	virtual ~Wavetable();
	virtual float* getSubtableForFrequency(float frequency);

protected:
	int lowestFrequency;
	int tableSize;
	float** subtables;
	virtual void calculateSubtables() = 0;
};



#endif  // WAVETABLE_H_INCLUDED
