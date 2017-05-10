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
#include "ModulationPopover.h"
#include "ModulatedComponent.h"

//==============================================================================
/*
*/
class FilterComponent    : public Component, public ComboBoxListener, public ModulationPopover::Listener, public DragAndDropListener
{
public:
    FilterComponent(OpenSynthAudioProcessor& processor);
    ~FilterComponent();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void modulationPopoverValueChanged(ModulationPopover* modulationPopover) override;
    void itemDropped(const int sourceID, const int destinationID) override;
    void mouseDown(const MouseEvent& event) override;

private:
    OpenSynthAudioProcessor& processor;
    
    ScopedPointer<ModulatedComponent> frequencyKnob;
    ScopedPointer<ParameterSlider> envelopeAmountKnob;
    ScopedPointer<ModulatedComponent> resonanceKnob;
    ScopedPointer<ParameterSlider> attackSlider;
    ScopedPointer<ParameterSlider> decaySlider;
    ScopedPointer<ParameterSlider> sustainSlider;
    ScopedPointer<ParameterSlider> releaseSlider;
    ScopedPointer<ComboBox> filterTypeComboBox;
    ScopedPointer<ModulationPopover> frequencyModulationPopover;
    Label attackLabel, decayLabel, sustainLabel, releaseLabel, frequencyLabel, envAmountLabel, resonanceLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};


#endif  // FILTERCOMPONENT_H_INCLUDED
