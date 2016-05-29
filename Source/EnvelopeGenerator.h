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

class EnvelopeSegment
{
public:
	typedef enum
	{
		EnvelopeSegmentTypeAttack,
		EnvelopeSegmentTypeDecay,
		EnvelopeSegmentTypeSustain,
		EnvelopeSegmentTypeRelease,
	} EnvelopeSegmentType;

	typedef enum
	{
		EnvelopeCurvatureLinear,
		EnvelopeCurvatureExponential,
	} EnvelopeCurvature;

	EnvelopeSegment()
	{
	}
	~EnvelopeSegment()
	{
	}

	double getCurrentAmp() { return currentAmp; }
	double getStartAmp() { return startAmp; }
	void setStartAmp(double startAmp) 
	{ 
		this->startAmp = startAmp;
		resetSegment();
	}
	double getFinalAmp() { return finalAmp; }
	void setFinalAmp(double finalAmp) 
	{ 
		this->finalAmp = finalAmp;
		resetSegment();
	}
	double getPeakAmp() { return peakAmp; }
	void setPeakAmp(double peakAmp) { this->peakAmp = peakAmp; }
	double getDurationInSamples() { return durationInSamples; }
	void setDurationInSamples(int durationInSamples) 
	{
		this->durationInSamples = durationInSamples;
		resetSegment();
	}
	void setType(EnvelopeSegmentType type) 
	{
		this->type = type;
		resetSegment();
	}
	void setCurvature(EnvelopeCurvature curvature) { this->curvature = curvature; }
	void resetSegment()
	{
		currentAmp = startAmp;
		if (durationInSamples < 1)
		{
			return;
		}
		range = finalAmp - startAmp;
		envInc = range / durationInSamples;

		if (type == EnvelopeSegmentTypeAttack)
		{
			offset = startAmp;
			expNow = expMin;
			expMul = std::pow((expMin + 1.0) / expMin, 1.0 / durationInSamples);
		}
		else if (type == EnvelopeSegmentTypeDecay)
		{
			offset = finalAmp;
			expNow = 1.0 + expMin;
			range *= (-1);
			expMul = std::pow(expMin / (1.0 + expMin), 1.0 / durationInSamples);
		}
	}

	void calculateNextAmp()
	{
		switch (type)
		{
		case EnvelopeSegmentTypeAttack:
		case EnvelopeSegmentTypeDecay:
			if (curvature == EnvelopeCurvatureLinear)
			{
				currentAmp += envInc;
			}
			else if (curvature == EnvelopeCurvatureExponential)
			{
				expNow *= expMul;
				currentAmp = ((expNow - expMin) * range) + offset;
			}
			break;
		}
	}

private:
	EnvelopeSegmentType type;
	EnvelopeCurvature curvature;
	int durationInSamples = 1;
	// Adjust to change curvature
	double expMin = 0.2;
	double expMul = std::pow((expMin + 1.0) / expMin, 1.0 / durationInSamples);
	double expNow = expMin;

	double envInc = 0.0;

	double currentAmp = 0.0;
	double startAmp = 0.0;
	double finalAmp = 0.0;
	double peakAmp = 0.0;
	double offset = 0.0;
	double range = 0.0;
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
	void setCurrentStartingSample(int currentStartingSample);
	void setDurationInSec(double durationInSec);
	void setStartingAmp(double startingAmp);

	int getCurrentStartingSample();

private:
	int currentStartingSample = 0;
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
