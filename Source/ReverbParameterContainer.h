/*
  ==============================================================================

    ReverbParameterContainer.h
    Created: 4 Dec 2016 7:36:08pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef REVERBPARAMETERCONTAINER_H_INCLUDED
#define REVERBPARAMETERCONTAINER_H_INCLUDED

#include "ParameterContainer.h"

class ReverbParameterContainer: public ParameterContainer
{
public:
    ReverbParameterContainer(int ID, OpenSynthAudioProcessor& processor) : ParameterContainer(ID, processor)
    {
        reverbSize = new AudioParameterFloat("reverbSize", "Reverb Size", 0.0f, 1.0f, 0.5f);
        processor.addParameter(reverbSize);
        reverbDamping = new AudioParameterFloat("reverbDamping", "Reverb Damping", 0.0f, 1.0f, 0.5f);
        processor.addParameter(reverbDamping);
        reverbDryLevel = new AudioParameterFloat("reverbDryLevel", "Reverb Dry Level", 0.0f, 1.0f, 0.4f);
        processor.addParameter(reverbDryLevel);
        reverbWetLevel = new AudioParameterFloat("reverbWetLevel", "Reverb Wet Level", 0.0f, 1.0f, 0.33f);
        processor.addParameter(reverbWetLevel);
        reverbWidth = new AudioParameterFloat("reverbWidth", "Reverb Width", 0.0f, 1.0f, 0.2f);
        processor.addParameter(reverbWidth);
        reverbEnabled = new AudioParameterBool("reverbEnabled", "Reverb Enabled", false);
        processor.addParameter(reverbEnabled);
    }
    
    virtual ~ReverbParameterContainer() {}
    
    AudioParameterFloat* getReverbSizeParameter() const { return reverbSize; }
    AudioParameterFloat* getReverbDampingParameter() const { return reverbDamping; }
    AudioParameterFloat* getReverbWetParameter() const { return reverbWetLevel; }
    AudioParameterFloat* getReverbDryParameter() const { return reverbDryLevel; }
    AudioParameterFloat* getReverbWidthParameter() const { return reverbWidth; }
    AudioParameterBool* getReverbEnabledParameter() const { return reverbEnabled; }
    
private:
    AudioParameterFloat* reverbSize;
    AudioParameterFloat* reverbDamping;
    AudioParameterFloat* reverbWetLevel;
    AudioParameterFloat* reverbDryLevel;
    AudioParameterFloat* reverbWidth;
    AudioParameterBool* reverbEnabled;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbParameterContainer);
};



#endif  // REVERBPARAMETERCONTAINER_H_INCLUDED
