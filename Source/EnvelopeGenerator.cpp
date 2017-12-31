/*
  ==============================================================================

    EnvelopeGenerator.cpp
    Created: 28 May 2016 10:58:28am
    Author:  Alex

  ==============================================================================
*/

#include "EnvelopeGenerator.h"

const String EnvelopeGenerator::Constants::Identifiers::EnvelopeGenerator = "envelope_generator";
const String EnvelopeGenerator::Constants::Identifiers::Attack = "attack";
const String EnvelopeGenerator::Constants::Identifiers::Decay = "decay";
const String EnvelopeGenerator::Constants::Identifiers::Sustain = "sustain";
const String EnvelopeGenerator::Constants::Identifiers::Release = "release";

const String EnvelopeGenerator::Constants::Names::EnvelopeGenerator = "Envelope Generator";
const String EnvelopeGenerator::Constants::Names::Attack = "Attack";
const String EnvelopeGenerator::Constants::Names::Decay = "Decay";
const String EnvelopeGenerator::Constants::Names::Sustain = "Sustain";
const String EnvelopeGenerator::Constants::Names::Release = "Release";

EnvelopeGenerator::EnvelopeGenerator(int ID,
                                     ModulationMatrix *modulationMatrix,
                                     AudioProcessorValueTreeState& audioProcessorValueTreeState,
                                     IDManager& idManager,
                                     int sampleRate) :
Module(ID,
       modulationMatrix,
       audioProcessorValueTreeState,
       idManager),
sampleRate(sampleRate),
durationInSec(2.0),
envInc(0.0)
{
	attackSegment.setCurvature(EnvelopeSegment::EnvelopeCurvatureExponential);
	decaySegment.setCurvature(EnvelopeSegment::EnvelopeCurvatureExponential);
    releaseSegment.setCurvature(EnvelopeSegment::EnvelopeCurvatureExponential);
    
    attackParameterID = idManager.getNewID();
    decayParameterID = idManager.getNewID();
    sustainParameterID = idManager.getNewID();
    releaseParameterID = idManager.getNewID();
    
    audioProcessorValueTreeState.createAndAddParameter(attackParameterStringID(),
                                                       Constants::Names::Attack,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 3.0f, 0.0f, 0.5f),
                                                       0.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(decayParameterStringID(),
                                                       Constants::Names::Decay,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 3.0f, 0.0f, 0.5f),
                                                       3.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(releaseParameterStringID(),
                                                       Constants::Names::Release,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 3.0f, 0.0f, 0.5f),
                                                       1.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(sustainParameterStringID(),
                                                       Constants::Names::Sustain,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f, 0.0f, 0.5f),
                                                       1.0f,
                                                       nullptr,
                                                       nullptr);
}

EnvelopeGenerator::~EnvelopeGenerator() {}

String EnvelopeGenerator::stringIdentifier() const
{
    return Constants::Identifiers::EnvelopeGenerator + String(ID);
}
String EnvelopeGenerator::attackParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Attack;
}

String EnvelopeGenerator::decayParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Decay;
}

String EnvelopeGenerator::sustainParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Sustain;
}

String EnvelopeGenerator::releaseParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Release;
}

void EnvelopeGenerator::calculateModulation(int numSamples)
{
	envelopeBuffer.resize(numSamples, 0);
	
	for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
	{
		switch (state)
		{
		case EnvelopeStateAttack:
			if (--envCount > 0)
			{
				currentValue = attackSegment.getCurrentAmp();
				attackSegment.calculateNextAmp();
			}
			else
			{
				currentValue = attackSegment.getFinalAmp();
				state = EnvelopeStateDecay;
				envCount = decaySegment.getDurationInSamples();
				attackSegment.resetSegment();
			}
			break;
		case EnvelopeStateDecay:
			if (--envCount > 0)
			{
				currentValue = decaySegment.getCurrentAmp();
				decaySegment.calculateNextAmp();
			}
			else
			{
				currentValue = decaySegment.getFinalAmp();
				state = EnvelopeStateSustain;
				decaySegment.resetSegment();
			}
			break;
		case EnvelopeStateSustain:
			currentValue = decaySegment.getFinalAmp();
			break;
		case EnvelopeStateRelease:
			if (--envCount > 0)
            {
                currentValue = releaseSegment.getCurrentAmp();
                releaseSegment.calculateNextAmp();
            }
            else
            {
                currentValue = 0.0;
            }
			break;
		}

		envelopeBuffer[sampleIdx] = currentValue;
	}
}

void EnvelopeGenerator::setEnvelopeState(EnvelopeState state)
{
    this->state = state;
    if (state == EnvelopeStateRelease)
    {
        envCount = releaseDuration;
        releaseSegment.setStartAmp(currentValue);
    }
};

float EnvelopeGenerator::getReleaseRate() const
{
    return *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Release);
}

void EnvelopeGenerator::reset()
{
	state = EnvelopeStateAttack;
    attackSegment.setStartAmp(0.0);
    attackSegment.setFinalAmp(1.0);
    decaySegment.setStartAmp(1.0);
    const float finalAmp = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Sustain);
    decaySegment.setFinalAmp(finalAmp);
    releaseSegment.setFinalAmp(0.0);
	attackSegment.resetSegment();
	decaySegment.resetSegment();
    releaseSegment.resetSegment();
	currentValue = attackSegment.getStartAmp();
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
    const float attack = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Attack);
	attackDuration = attack * sampleRate;
    const float decay = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Decay);
	decayDuration = decay * sampleRate;
	decayStart = attackDuration;
    const float release = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Release);
    releaseDuration = release * sampleRate;

	attackSegment.setDurationInSamples(attackDuration);
	decaySegment.setDurationInSamples(decayDuration);
    releaseSegment.setDurationInSamples(releaseDuration);
	envCount = attackDuration;
}

