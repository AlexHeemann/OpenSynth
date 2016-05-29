/*
  ==============================================================================

    EnvelopeGenerator.h
    Created: 28 May 2016 10:58:28am
    Author:  Alex

  ==============================================================================
*/

#ifndef ENVELOPEGENERATOR_H_INCLUDED
#define ENVELOPEGENERATOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeSegment.h"

class EnvelopeGenerator
{
public:
	typedef enum
	{
		EnvelopeStateAttack,
		EnvelopeStateDecay,
		EnvelopeStateSustain,
		EnvelopeStateRelease
	} EnvelopeState;

	EnvelopeGenerator(int sampleRate);
	EnvelopeGenerator();
	~EnvelopeGenerator();
	// Contains the values for the current buffer
	std::vector<double> envelopeBuffer;

	void calculateEnvelopeBuffer(int numSamples);
	void resetEnvelope();

	void setAttackRate(double attackRate);
	void setDecayRate(double decayRate);
	void setPeakAmp(double peakAmp);
	void setSampleRate(int sampleRate);
	void setDurationInSec(double durationInSec);
	void setStartingAmp(double startingAmp);

	int getCurrentStartingSample();

private:
	double currentAmp = 0;
	double startingAmp = 0;
	int sampleRate;
	double durationInSec;
	// Duration in samples
	int totalDuration;
	int attackDuration;
	int sustainDuration;
	int decayDuration;
	int decayStart;
	EnvelopeState state = EnvelopeStateAttack;
	EnvelopeSegment attackSegment;
	EnvelopeSegment decaySegment;

	double attackRate;
	double decayRate;
	double peakAmp;

	double envInc;
	double envCount;

	void calculateDurations();


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGenerator)
};




#endif  // ENVELOPEGENERATOR_H_INCLUDED
