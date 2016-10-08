/*
  ==============================================================================

    AmpComponent.h
    Created: 6 Oct 2016 3:15:30pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef AMPCOMPONENT_H_INCLUDED
#define AMPCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterSlider.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class AmpComponent    : public Component
{
public:
    AmpComponent(NoisemakerAudioProcessor& processor);
    ~AmpComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpComponent)
    
    NoisemakerAudioProcessor& processor;
    
    ScopedPointer<ParameterSlider> gainKnob;
    ScopedPointer<ParameterSlider> attackSlider;
    ScopedPointer<ParameterSlider> decaySlider;
    ScopedPointer<ParameterSlider> sustainSlider;
    ScopedPointer<ParameterSlider> releaseSlider;
    Label attackLabel, decayLabel, sustainLabel, releaseLabel, ampLabel;
};


#endif  // AMPCOMPONENT_H_INCLUDED
