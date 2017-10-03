/*
  ==============================================================================

    Utility.h
    Created: 8 Aug 2017 6:06:56am
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

double getFrequencyFromFloatNote(float note)
{
    double frequencyOfA = 440.0;
    return frequencyOfA * powf (2.0, (note - 69) / 12.0);
}
