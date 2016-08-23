/*
  ==============================================================================

    EnvelopeGenerator.cpp
    Created: 28 May 2016 10:58:28am
    Author:  Alex

  ==============================================================================
*/

#include "EnvelopeGenerator.h"

EnvelopeGenerator::EnvelopeGenerator() : sampleRate(0.0), attackRate(1.0), decayRate(1.0), currentAmp(0.0), durationInSec(2.0), envInc(0.0)
{
	setAttackLevel(1.0);
	setDecayLevel(0.0);
	setStartingAmp(0.0);
	calculateDurations();
	resetEnvelope();
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
	this->attackSegment.setStartAmp(startingAmp);
}

void EnvelopeGenerator::setAttackLevel(double attackLevel)
{
	this->attackLevel = std::fmin(1.0, attackLevel);
	this->attackSegment.setFinalAmp(this->attackLevel);
	this->decaySegment.setStartAmp(this->attackLevel);
}

void EnvelopeGenerator::setDecayLevel(double decayLevel)
{
	this->decayLevel = std::fmin(1.0, decayLevel);
	this->decaySegment.setFinalAmp(this->decayLevel);
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

