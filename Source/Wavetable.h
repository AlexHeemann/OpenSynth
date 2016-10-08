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
	Wavetable(float lowestFrequency, int tableSize, int sampleRate);
	virtual ~Wavetable();
	virtual float* getSubtableForFrequency(float frequency);
    int getTableSize();
    virtual void setSampleRate(int sampleRate);

protected:
	int lowestFrequency;
	int tableSize;
    int sampleRate;
	float** subtables;
    
    double currentAngle, angleDelta, frequency, period;
    double frqRad;
    double twoPi = 2.0 * double_Pi;
    
    std::vector<int> partialMultiples;
    std::vector<double> partialAmplitudes;
    /* The current phase of each partial */
    std::vector<double> phases;
    /* The phase increments of each partial */
    std::vector<double> phaseIncrements;
    /* Scale to normalize amplitude */
    double scale;
    std::vector<double> sigma;
    
    virtual void calculateSubtables() { /* override in subclass */ } ;
};



#endif  // WAVETABLE_H_INCLUDED
