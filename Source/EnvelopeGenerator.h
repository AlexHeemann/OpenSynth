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

class EnvelopeGenerator : public Module
{
public:
    
    struct Constants
    {
        struct Identifiers
        {
            static const String EnvelopeGenerator;
            static const String Attack;
            static const String Decay;
            static const String Sustain;
            static const String Release;
        };
        struct Names
        {
            static const String EnvelopeGenerator;
            static const String Attack;
            static const String Decay;
            static const String Sustain;
            static const String Release;
        };
    };
    
    EnvelopeGenerator(int ID,
                      ModulationMatrix *modulationMatrix,
                      AudioProcessorValueTreeState& audioProcessorValueTreeState,
                      IDManager& idManager,
                      int sampleRate);
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

    int attackParameterID;
    int decayParameterID;
    int sustainParameterID;
    int releaseParameterID;
    
    String stringIdentifier() const override;
    String attackParameterStringID() const;
    String decayParameterStringID() const;
    String sustainParameterStringID() const;
    String releaseParameterStringID() const;
    
	double envInc;
	double envCount;

	void calculateDurations();


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGenerator)
};




#endif  // ENVELOPEGENERATOR_H_INCLUDED
