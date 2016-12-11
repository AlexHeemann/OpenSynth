/*
  ==============================================================================

    EnvelopeParameterContainer.h
    Created: 4 Dec 2016 7:37:33pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef ENVELOPEPARAMETERCONTAINER_H_INCLUDED
#define ENVELOPEPARAMETERCONTAINER_H_INCLUDED

#include "ParameterContainer.h"

class EnvelopeParameterContainer: public ParameterContainer
{
public:
    EnvelopeParameterContainer(AudioProcessor& processor, int envelopeIndex) : processor(processor), envelopeIndex(envelopeIndex)
    {
        processor.addParameter(attackRate = new AudioParameterFloat("attack " + String(envelopeIndex), "Envelope " + String(envelopeIndex) + " Attack", 0.0f, 3.0f, 0.0f));
        attackRate->range.skew = 0.5;
        processor.addParameter(decayRate = new AudioParameterFloat("decay " + String(envelopeIndex), "Envelope " + String(envelopeIndex) + " Decay", 0.0f, 3.0f, 3.0f));
        decayRate->range.skew = 0.5;
        processor.addParameter(releaseRate = new AudioParameterFloat("release " + String(envelopeIndex), "Envelope " + String(envelopeIndex) + " Release", 0.0f, 3.0f, 1.0f));
        releaseRate->range.skew = 0.5;
        processor.addParameter(sustainLevel = new AudioParameterFloat("sustain " + String(envelopeIndex), "Envelope " + String(envelopeIndex) + " Sustain", 0.0f, 1.0f, 1.0f));
    }
    
    virtual ~EnvelopeParameterContainer() {}
    
    AudioParameterFloat* getAttackRateParameter() const { return attackRate; }
    AudioParameterFloat* getDecayRateParameter() const { return decayRate; }
    AudioParameterFloat* getReleaseRateParameter() const { return releaseRate; }
    AudioParameterFloat* getSustainLevelParameter() const { return sustainLevel; }
    
private:
    AudioProcessor& processor;
    int envelopeIndex;
    
    AudioParameterFloat* attackRate;
    AudioParameterFloat* decayRate;
    AudioParameterFloat* releaseRate;
    AudioParameterFloat* sustainLevel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeParameterContainer)
};



#endif  // ENVELOPEPARAMETERCONTAINER_H_INCLUDED
