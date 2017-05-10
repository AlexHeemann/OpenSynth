/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterSlider.h"
#include "ModulationPlug.h"
#include "EnvelopeParameterContainer.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class EnvelopeComponent  : public Component,
                           public SliderListener
{
public:
    //==============================================================================
    EnvelopeComponent (EnvelopeParameterContainer& parameterContainer);
    ~EnvelopeComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ParameterContainer& parameterContainer;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> envelopeTitleLabel;
    ScopedPointer<ParameterSlider> attackSlider;
    ScopedPointer<ParameterSlider> decaySlider;
    ScopedPointer<ParameterSlider> sustainSlider;
    ScopedPointer<ParameterSlider> releaseSlider;
    ScopedPointer<Label> attackLabel;
    ScopedPointer<Label> decayLabel;
    ScopedPointer<Label> sustainLabel;
    ScopedPointer<Label> releaseLabel;
    ScopedPointer<ModulationPlug> modulationPlug;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
