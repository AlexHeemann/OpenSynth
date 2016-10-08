/*
  ==============================================================================

    SawtoothWavetable.h
    Created: 20 Sep 2016 7:43:12pm
    Author:  Alex

  ==============================================================================
*/

#ifndef SAWTOOTHWAVETABLE_H_INCLUDED
#define SAWTOOTHWAVETABLE_H_INCLUDED

#include "Wavetable.h"

class SawtoothWavetable : public Wavetable
{
public:
	SawtoothWavetable(float lowestFrequency, int tableSize, int sampleRate);
	~SawtoothWavetable();
    
protected:
	virtual void calculateSubtables() override;
};



#endif  // SAWTOOTHWAVETABLE_H_INCLUDED
