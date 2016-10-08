/*
  ==============================================================================

    SineWavetable.h
    Created: 8 Oct 2016 7:12:45pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef SINEWAVETABLE_H_INCLUDED
#define SINEWAVETABLE_H_INCLUDED

#include "Wavetable.h"

class SineWavetable : public Wavetable
{
public:
    SineWavetable(float lowestFrequency, int tableSize, int sampleRate);
    ~SineWavetable();
    
protected:
    virtual void calculateSubtables() override;
};

#endif  // SINEWAVETABLE_H_INCLUDED
