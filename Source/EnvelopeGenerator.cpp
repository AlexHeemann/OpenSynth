/*
  ==============================================================================

    EnvelopeGenerator.cpp
    Created: 28 May 2016 10:58:28am
    Author:  Alex

  ==============================================================================
*/

#include "EnvelopeGenerator.h"

EnvelopeGenerator::EnvelopeGenerator() : currentAmp(0.0), sampleRate(0.0), durationInSec(2.0), envInc(0.0)
{
    attackRate = new AudioParameterFloat("attack", "Envelope Attack", 0.0f, 3.0f, 1.0f);
    decayRate = new AudioParameterFloat("decay", "Envelope Decay", 0.0f, 3.0f, 1.0f);
    releaseRate = new AudioParameterFloat("release", "Envelope Release", 0.0f, 3.0f, 1.0f);
    sustainLevel = new AudioParameterFloat("sustain", "Envelope Sustain", 0.0f, 1.0f, 1.0f);
    resetEnvelope();
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


void EnvelopeGenerator::resetEnvelope()
{
	state = EnvelopeStateAttack;
    attackSegment.setStartAmp(0.0);
    attackSegment.setFinalAmp(1.0);
    decaySegment.setStartAmp(1.0);
    decaySegment.setFinalAmp(sustainLevel->get());
    releaseSegment.setStartAmp(sustainLevel->get());
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
	calculateDurations();
}

void EnvelopeGenerator::setDurationInSec(double durationInSec)
{
	this->durationInSec = durationInSec;
	calculateDurations();
}

void EnvelopeGenerator::calculateDurations()
{
	attackDuration = attackRate->get() * sampleRate;
	decayDuration = decayRate->get() * sampleRate;
	decayStart = attackDuration;
    releaseDuration = releaseRate->get() * sampleRate;

	attackSegment.setDurationInSamples(attackDuration);
	decaySegment.setDurationInSamples(decayDuration);
    releaseSegment.setDurationInSamples(releaseDuration);
	envCount = attackDuration;
}

