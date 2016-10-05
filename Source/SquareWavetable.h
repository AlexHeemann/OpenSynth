/*
  ==============================================================================

    SquareWavetable.h
    Created: 5 Oct 2016 6:42:41pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef SQUAREWAVETABLE_H_INCLUDED
#define SQUAREWAVETABLE_H_INCLUDED

#include "Wavetable.h"

class SquareWavetable : public Wavetable
{
public:
    SquareWavetable(float lowestFrequency, int tableSize, int sampleRate);
    ~SquareWavetable();
    
protected:
    virtual void calculateSubtables() override;
};


#endif  // SQUAREWAVETABLE_H_INCLUDED
