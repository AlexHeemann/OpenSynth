/*
  ==============================================================================

    FilterComponent.h
    Created: 8 Oct 2016 4:47:11pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef FILTERCOMPONENT_H_INCLUDED
#define FILTERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterSlider.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterComponent    : public Component, public ComboBoxListener
{
public:
    FilterComponent(NoisemakerAudioProcessor& processor);
    ~FilterComponent();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

private:
    NoisemakerAudioProcessor& processor;
    
    ScopedPointer<ParameterSlider> frequencyKnob;
    ScopedPointer<ParameterSlider> envelopeAmountKnob;
    ScopedPointer<ParameterSlider> resonanceKnob;
    ScopedPointer<ParameterSlider> attackSlider;
    ScopedPointer<ParameterSlider> decaySlider;
    ScopedPointer<ParameterSlider> sustainSlider;
    ScopedPointer<ParameterSlider> releaseSlider;
    ScopedPointer<ComboBox> filterTypeComboBox;
    Label attackLabel, decayLabel, sustainLabel, releaseLabel, frequencyLabel, envAmountLabel, resonanceLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};


#endif  // FILTERCOMPONENT_H_INCLUDED
