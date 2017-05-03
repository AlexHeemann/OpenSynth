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
#include "PluginProcessor.h"
#include "DelayParameterContainer.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class DelayComponent  : public Component,
                        public SliderListener,
                        public ButtonListener
{
public:
    //==============================================================================
    DelayComponent (DelayParameterContainer& parameterContainer);
    ~DelayComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    DelayParameterContainer& parameterContainer;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ParameterSlider> timeKnob;
    ScopedPointer<ParameterSlider> feedKnob;
    ScopedPointer<ParameterSlider> spreadKnob;
    ScopedPointer<ParameterSlider> mixKnob;
    ScopedPointer<Label> timeLabel;
    ScopedPointer<Label> feedLabel;
    ScopedPointer<Label> spreadLabel;
    ScopedPointer<Label> mixLabel;
    ScopedPointer<Label> delayTitleLabel;
    ScopedPointer<ToggleButton> delayToggleButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
