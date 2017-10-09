/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterSlider.h"
#include "PluginEditor.h"
#include "ModulatedComponent.h"

class OscillatorParameterContainer;
class ModulationMatrix;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class OscillatorComponent  : public Component,
                             public DragAndDropListener,
                             public ComboBox::Listener
{
public:
    //==============================================================================
    OscillatorComponent (OpenSynthAudioProcessorEditor &editor, OscillatorParameterContainer* parameterContainer, ModulationMatrix* modulationMatrix);
    ~OscillatorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void itemDropped(const int sourceID, const int destinationID) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    OpenSynthAudioProcessorEditor& editor;
    OscillatorParameterContainer* parameterContainer;
    ModulationMatrix* modulationMatrix;
    Waveform waveformForId(int waveformId);
    std::unordered_map<int, ModulatedComponent*> idToComponent;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> oscComboBox;
    ScopedPointer<Label> gainLabel;
    ScopedPointer<Label> titleLabel;
    ScopedPointer<Label> osc1SemiLabel;
    ScopedPointer<Label> osc1CentsLabel;
    ScopedPointer<ModulatedComponent> oscGainSlider;
    ScopedPointer<ModulatedComponent> oscSemiSlider;
    ScopedPointer<ModulatedComponent> oscCentSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
