/*
  ==============================================================================

    EnvelopeSegment.h
    Created: 29 May 2016 6:48:19pm
    Author:  Alex

  ==============================================================================
*/

#ifndef ENVELOPESEGMENT_H_INCLUDED
#define ENVELOPESEGMENT_H_INCLUDED

#include <cmath>

class EnvelopeSegment
{
public:
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
	
	void setCurvature(EnvelopeCurvature curvature) { this->curvature = curvature; }

	virtual void resetSegment()
	{
		currentAmp = startAmp;
		if (durationInSamples < 1)
		{
			return;
		}
		range = finalAmp - startAmp;
		envInc = range / durationInSamples;
	}

	void calculateNextAmp()
	{
		if (curvature == EnvelopeCurvatureLinear)
		{
			currentAmp += envInc;
		}
		else if (curvature == EnvelopeCurvatureExponential)
		{
			expNow *= expMul;
			currentAmp = ((expNow - expMin) * range) + offset;
		}
	}

	void setExpMin(double expMin) 
	{ 
		this->expMin = expMin; 
		resetSegment();
	}
	double getExpMin() { return this->expMin; }


protected:
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

class EnvelopeSegmentAttack : public EnvelopeSegment
{
public:
	EnvelopeSegmentAttack() : EnvelopeSegment()
	{

	}
	~EnvelopeSegmentAttack()
	{

	}

	virtual void resetSegment()
	{
		EnvelopeSegment::resetSegment();
		
		offset = startAmp;
		expNow = expMin;
		expMul = std::pow((expMin + 1.0) / expMin, 1.0 / durationInSamples);
	}
};

class EnvelopeSegmentDecay : public EnvelopeSegment
{
public:
	EnvelopeSegmentDecay() : EnvelopeSegment()
	{

	}
	~EnvelopeSegmentDecay()
	{

	}

	virtual void resetSegment()
	{
		EnvelopeSegment::resetSegment();

		offset = finalAmp;
		expNow = 1.0 + expMin;
		range *= (-1);
		expMul = std::pow(expMin / (1.0 + expMin), 1.0 / durationInSamples);
	}
};


#endif  // ENVELOPESEGMENT_H_INCLUDED
