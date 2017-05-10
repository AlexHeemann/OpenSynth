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
    EnvelopeParameterContainer(AudioProcessor& processor, String name) : ModulationParameterContainer(processor, name)
    {
        processor.addParameter(attackRate = new AudioParameterFloat(name + " attack", name + " Attack", 0.0f, 3.0f, 0.0f));
        attackRate->range.skew = 0.5;
        processor.addParameter(decayRate = new AudioParameterFloat(name + " decay", name + " Decay", 0.0f, 3.0f, 3.0f));
        decayRate->range.skew = 0.5;
        processor.addParameter(releaseRate = new AudioParameterFloat(name + " release", name + " Release", 0.0f, 3.0f, 1.0f));
        releaseRate->range.skew = 0.5;
        processor.addParameter(sustainLevel = new AudioParameterFloat(name + " sustain", name + " Sustain", 0.0f, 1.0f, 1.0f));
    }
    
    virtual ~EnvelopeParameterContainer() {}
    
    AudioParameterFloat* getAttackRateParameter() const { return attackRate; }
    AudioParameterFloat* getDecayRateParameter() const { return decayRate; }
    AudioParameterFloat* getReleaseRateParameter() const { return releaseRate; }
    AudioParameterFloat* getSustainLevelParameter() const { return sustainLevel; }
    
private:
    AudioParameterFloat* attackRate;
    AudioParameterFloat* decayRate;
    AudioParameterFloat* releaseRate;
    AudioParameterFloat* sustainLevel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeParameterContainer)
};



#endif  // ENVELOPEPARAMETERCONTAINER_H_INCLUDED
