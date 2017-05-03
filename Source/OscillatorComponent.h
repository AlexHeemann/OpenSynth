/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterSlider.h"
#include "OscillatorParameterContainer.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class OscillatorComponent  : public Component,
                             public ComboBoxListener
{
public:
    //==============================================================================
    OscillatorComponent (OscillatorParameterContainer& parameterContainer);
    ~OscillatorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    OscillatorParameterContainer& parameterContainer;
    Waveform waveformForId(int waveformId);
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> osc1ComboBox;
    ScopedPointer<ParameterSlider> oscMixSlider;
    ScopedPointer<ComboBox> osc2ComboBox;
    ScopedPointer<Label> mixLabel;
    ScopedPointer<Label> titleLabel;
    ScopedPointer<ParameterSlider> osc1SemiSlider;
    ScopedPointer<ParameterSlider> osc2SemiSlider;
    ScopedPointer<ParameterSlider> osc1CentSlider;
    ScopedPointer<ParameterSlider> osc2CentSlider;
    ScopedPointer<Label> osc1SemiLabel;
    ScopedPointer<Label> osc1CentsLabel;
    ScopedPointer<Label> osc2SemiLabel;
    ScopedPointer<Label> osc2CentsLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
