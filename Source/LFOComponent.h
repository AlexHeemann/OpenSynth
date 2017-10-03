/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ParameterSlider.h"
#include "ModulationPlug.h"
#include "ModulatedComponent.h"
#include "PluginEditor.h"

class LFOParameterContainer;
class ModulationMatrix;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class LFOComponent  : public Component,
                      public ModulationPopover::Listener,
                      public DragAndDropListener,
                      public ComboBoxListener
{
public:
    //==============================================================================
    LFOComponent (OpenSynthAudioProcessorEditor &editor, LFOParameterContainer* parameterContainer, ModulationMatrix* modulationMatrix);
    ~LFOComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void modulationPopoverValueChanged(ModulationPopover* modulationPopover) override;
    void itemDropped(const int sourceID, const int destinationID) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    OpenSynthAudioProcessorEditor& editor;
    LFOParameterContainer* parameterContainer;
    ScopedPointer<ModulationPopover> lfoFrequencyModulationPopover;
    ModulationMatrix* modulationMatrix;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> lfoTitleLabel;
    ScopedPointer<Label> label;
    ScopedPointer<ComboBox> waveformComboBox;
    ScopedPointer<ModulationPlug> modulationPlug;
    ScopedPointer<ModulatedComponent> frequencyKnob;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
