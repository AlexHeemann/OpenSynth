/*
  ==============================================================================

    EnvelopeGenerator.cpp
    Created: 28 May 2016 10:58:28am
    Author:  Alex

  ==============================================================================
*/

#include "EnvelopeGenerator.h"
#include "EnvelopeParameterContainer.h"

EnvelopeGenerator::EnvelopeGenerator() : currentAmp(0.0), sampleRate(0.0), durationInSec(2.0), envInc(0.0)
{
	attackSegment.setCurvature(EnvelopeSegment::EnvelopeCurvatureExponential);
	decaySegment.setCurvature(EnvelopeSegment::EnvelopeCurvatureExponential);
    releaseSegment.setCurvature(EnvelopeSegment::EnvelopeCurvatureExponential);
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
				state = EnvelopeStateSustain;
				decaySegment.resetSegment();
			}
			break;
		case EnvelopeStateSustain:
			currentAmp = decaySegment.getFinalAmp();
			break;
		case EnvelopeStateRelease:
			if (--envCount > 0)
            {
                currentAmp = releaseSegment.getCurrentAmp();
                releaseSegment.calculateNextAmp();
            }
            else
            {
                currentAmp = 0.0;
            }
			break;
		}

		envelopeBuffer[sampleIdx] = currentAmp;
	}
}

void EnvelopeGenerator::setEnvelopeState(EnvelopeState state)
{
    this->state = state;
    if (state == EnvelopeStateRelease)
    {
        envCount = releaseDuration;
        releaseSegment.setStartAmp(currentAmp);
    }
};

float EnvelopeGenerator::getReleaseRate() const
{
    return envelopeParameterContainer->getReleaseRateParameter()->get();
}

void EnvelopeGenerator::resetEnvelope()
{
	state = EnvelopeStateAttack;
    attackSegment.setStartAmp(0.0);
    attackSegment.setFinalAmp(1.0);
    decaySegment.setStartAmp(1.0);
    decaySegment.setFinalAmp(envelopeParameterContainer->getSustainLevelParameter()->get());
    releaseSegment.setFinalAmp(0.0);
	attackSegment.resetSegment();
	decaySegment.resetSegment();
    releaseSegment.resetSegment();
	currentAmp = attackSegment.getStartAmp();
	envCount = attackSegment.getDurationInSamples();
    
    calculateDurations();
}

void EnvelopeGenerator::setSampleRate(int sampleRate)
{
	this->sampleRate = sampleRate;
}

void EnvelopeGenerator::setDurationInSec(double durationInSec)
{
	this->durationInSec = durationInSec;
}

void EnvelopeGenerator::calculateDurations()
{
	attackDuration = envelopeParameterContainer->getAttackRateParameter()->get() * sampleRate;
	decayDuration = envelopeParameterContainer->getDecayRateParameter()->get() * sampleRate;
	decayStart = attackDuration;
    releaseDuration = envelopeParameterContainer->getReleaseRateParameter()->get() * sampleRate;

	attackSegment.setDurationInSamples(attackDuration);
	decaySegment.setDurationInSamples(decayDuration);
    releaseSegment.setDurationInSamples(releaseDuration);
	envCount = attackDuration;
}

