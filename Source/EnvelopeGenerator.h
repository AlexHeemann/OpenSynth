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
#include "Module.h"
#include "EnvelopeState.h"

class EnvelopeParameterContainer;

// Abstract base class for all things modulating
class Modulator
{
public:
	Modulator() {};
	virtual ~Modulator() {};

	virtual std::vector<double> getModulationBuffer() = 0;
	virtual void calculateModulationBuffer(int numSamples) = 0;

};

class EnvelopeGenerator : public Module
{
public:
	EnvelopeGenerator(EnvelopeParameterContainer* parameterContainer);
	virtual ~EnvelopeGenerator();
	// Contains the values for the current buffer
	std::vector<double> envelopeBuffer;
    std::vector<double> releaseBuffer;

    void setSampleRate(int sampleRate) override;
	void calculateModulation(int numSamples) override;
	void reset() override;
    float getReleaseRate() const;
    
	void setDurationInSec(double durationInSec);
    void setEnvelopeState(EnvelopeState state);
    void setParameterContainer(EnvelopeParameterContainer* parameterContainer)
    {
        this->parameterContainer = parameterContainer;
    }
    
private:
	double startingAmp = 0;
	int sampleRate;
	double durationInSec;
	// Duration in samples
	int attackDuration;
	int decayDuration;
	int decayStart;
    int releaseDuration;
	EnvelopeState state = EnvelopeStateAttack;
	EnvelopeSegmentAttack attackSegment;
	EnvelopeSegmentDecay decaySegment;
    EnvelopeSegmentRelease releaseSegment;
    EnvelopeParameterContainer* parameterContainer;

	double envInc;
	double envCount;

	void calculateDurations();


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGenerator)
};




#endif  // ENVELOPEGENERATOR_H_INCLUDED
