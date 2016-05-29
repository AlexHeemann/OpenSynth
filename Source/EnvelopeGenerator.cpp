/*
  ==============================================================================

    EnvelopeGenerator.cpp
    Created: 28 May 2016 10:58:28am
    Author:  Alex

  ==============================================================================
*/

#include "EnvelopeGenerator.h"

EnvelopeGenerator::EnvelopeGenerator(int sampleRate) : sampleRate(sampleRate), attackRate(1.0), peakAmp(1.0), decayRate(1.0), currentAmp(0.0), currentStartingSample(0), durationInSec(2.0), envInc(0)
{
	calculateDurations();
}

EnvelopeGenerator::EnvelopeGenerator() : sampleRate(0.0), attackRate(1.0), decayRate(1.0), peakAmp(1.0), currentAmp(0.0), currentStartingSample(0), durationInSec(2.0), envInc(0.0)
{
	calculateDurations();
	resetEnvelope();
	attackSegment.setType(EnvelopeSegment::EnvelopeSegmentTypeAttack);
	decaySegment.setType(EnvelopeSegment::EnvelopeSegmentTypeDecay);
	attackSegment.setCurvature(EnvelopeSegment::EnvelopeCurvatureExponential);
	decaySegment.setCurvature(EnvelopeSegment::EnvelopeCurvatureExponential);
}

EnvelopeGenerator::~EnvelopeGenerator() {}

void EnvelopeGenerator::calculateEnvelopeBuffer(int numSamples)
{
	envelopeBuffer.resize(numSamples, 0);
	
	for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
	{
		switch (state)
		{
		case EnvelopeStateAttack:
			if (--envCount > 0)
			{
				currentAmp = attackSegment.getCurrentAmp();
				attackSegment.calculateNextAmp();
			}
			else
			{
				currentAmp = attackSegment.getFinalAmp();
				state = EnvelopeStateDecay;
				envCount = decaySegment.getDurationInSamples();
				attackSegment.resetSegment();
			}
			break;
		case EnvelopeStateDecay:
			if (--envCount > 0)
			{
				currentAmp = decaySegment.getCurrentAmp();
				decaySegment.calculateNextAmp();
			}
			else
			{
				currentAmp = decaySegment.getFinalAmp();
				state = EnvelopeStateRelease;
				decaySegment.resetSegment();
			}
			break;
		case EnvelopeStateSustain:
			currentAmp = decaySegment.getFinalAmp();
			break;
		case EnvelopeStateRelease:
			currentAmp = 0.0;
			break;
		}

		envelopeBuffer[sampleIdx] = currentAmp;
	}
}

void EnvelopeGenerator::resetEnvelope()
{
	currentStartingSample = 0;
	state = EnvelopeStateAttack;
	calculateDurations();
	attackSegment.resetSegment();
	decaySegment.resetSegment();
	currentAmp = attackSegment.getStartAmp();
	envCount = attackSegment.getDurationInSamples();
}

void EnvelopeGenerator::setAttackRate(double attackRate)
{
	this->attackRate = attackRate;
	calculateDurations();
}

void EnvelopeGenerator::setDecayRate(double decayRate)
{
	this->decayRate = decayRate;
	calculateDurations();
}

void EnvelopeGenerator::setPeakAmp(double peakAmp)
{
	this->peakAmp = std::fmin(1.0, peakAmp);
	this->attackSegment.setPeakAmp(this->peakAmp);
	this->attackSegment.setStartAmp(0.0);
	this->attackSegment.setFinalAmp(this->peakAmp);
	this->decaySegment.setStartAmp(attackSegment.getFinalAmp());
	this->decaySegment.setFinalAmp(0.0);
}

void EnvelopeGenerator::setSampleRate(int sampleRate)
{
	this->sampleRate = sampleRate;
	calculateDurations();
}

void EnvelopeGenerator::setDurationInSec(double durationInSec)
{
	this->durationInSec = durationInSec;
	calculateDurations();
}

void EnvelopeGenerator::setStartingAmp(double startingAmp)
{
	this->startingAmp = startingAmp;
}

int EnvelopeGenerator::getCurrentStartingSample()
{
	return currentStartingSample;
}

void EnvelopeGenerator::calculateDurations()
{
	totalDuration = durationInSec * sampleRate;
	attackDuration = attackRate * sampleRate;
	decayDuration = decayRate * sampleRate;
	decayStart = totalDuration - decayDuration;

	attackSegment.setDurationInSamples(attackDuration);
	decaySegment.setDurationInSamples(decayDuration);
	envCount = attackDuration;
}

