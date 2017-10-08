/*
  ==============================================================================

    EnvelopeParameterContainer.h
    Created: 4 Dec 2016 7:37:33pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef ENVELOPEPARAMETERCONTAINER_H_INCLUDED
#define ENVELOPEPARAMETERCONTAINER_H_INCLUDED

#include "ModulationParameterContainer.h"

class EnvelopeParameterContainer: public ModulationParameterContainer
{
public:
    EnvelopeParameterContainer(int ID, OpenSynthAudioProcessor& processor) : ModulationParameterContainer(ID, processor)
    {
        attackParameterID = processor.getIDManager().getNewID();
        decayParameterID = processor.getIDManager().getNewID();
        sustainParameterID = processor.getIDManager().getNewID();
        releaseParameterID = processor.getIDManager().getNewID();
        
        processor.addParameter(attackRate = new AudioParameterFloat("envelope_" + String(ID) + "_attack",  "Envelope " + String(ID) + " Attack", 0.0f, 3.0f, 0.0f));
        attackRate->range.skew = 0.5;
        processor.addParameter(decayRate = new AudioParameterFloat("envelope_" + String(ID) + "_decay", "Envelope " + String(ID) + " Decay", 0.0f, 3.0f, 3.0f));
        decayRate->range.skew = 0.5;
        processor.addParameter(releaseRate = new AudioParameterFloat("envelope_" + String(ID) + "_release", "Envelope " + String(ID) + " Release", 0.0f, 3.0f, 1.0f));
        releaseRate->range.skew = 0.5;
        processor.addParameter(sustainLevel = new AudioParameterFloat("envelope_" + String(ID) + "_sustain", "Envelope " + String(ID) + " Sustain", 0.0f, 1.0f, 1.0f));
    }
    
    virtual ~EnvelopeParameterContainer() {}
    
    AudioParameterFloat* getAttackRateParameter() const { return attackRate; }
    AudioParameterFloat* getDecayRateParameter() const { return decayRate; }
    AudioParameterFloat* getReleaseRateParameter() const { return releaseRate; }
    AudioParameterFloat* getSustainLevelParameter() const { return sustainLevel; }
    
    const int getAttackParameterID() const { return attackParameterID; }
    const int getDecayParameterID() const { return decayParameterID; }
    const int getSustainParameterID() const { return sustainParameterID; }
    const int getReleaseParameterID() const { return releaseParameterID; }
    
private:
    AudioParameterFloat* attackRate;
    AudioParameterFloat* decayRate;
    AudioParameterFloat* releaseRate;
    AudioParameterFloat* sustainLevel;
    
    int attackParameterID = 0;
    int decayParameterID = 0;
    int sustainParameterID = 0;
    int releaseParameterID = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeParameterContainer)
};



#endif  // ENVELOPEPARAMETERCONTAINER_H_INCLUDED
