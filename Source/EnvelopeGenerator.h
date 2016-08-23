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

// Abstract base class for all things modulating
class Modulator
{
public:
	Modulator() {};
	virtual ~Modulator() {};

	virtual std::vector<double> getModulationBuffer() = 0;
	virtual void calculateModulationBuffer(int numSamples) = 0;

};

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

	EnvelopeGenerator();
	virtual ~EnvelopeGenerator();
	// Contains the values for the current buffer
	std::vector<double> envelopeBuffer;

	void calculateEnvelopeBuffer(int numSamples);
	void resetEnvelope();

	void setAttackRate(double attackRate);
	void setDecayRate(double decayRate);
	void setSampleRate(int sampleRate);
	void setDurationInSec(double durationInSec);
	void setStartingAmp(double startingAmp);
	void setAttackLevel(double attackLevel);
	void setDecayLevel(double decayLevel);

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
	EnvelopeSegmentAttack attackSegment;
	EnvelopeSegmentDecay decaySegment;

	// Modifiable from the outside
	double attackRate;
	double decayRate;
	double attackLevel;
	double decayLevel;

	double envInc;
	double envCount;

	void calculateDurations();


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGenerator)
};




#endif  // ENVELOPEGENERATOR_H_INCLUDED
