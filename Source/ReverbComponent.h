/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_F31C8E96463616E__
#define __JUCE_HEADER_F31C8E96463616E__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterSlider.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ReverbComponent  : public Component,
                         public ButtonListener
{
public:
    //==============================================================================
    ReverbComponent (NoisemakerAudioProcessor& processor);
    ~ReverbComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    NoisemakerAudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> reverbTitleLabel;
    ScopedPointer<ParameterSlider> reverbSizeKnob;
    ScopedPointer<ParameterSlider> reverbDampingKnob;
    ScopedPointer<ParameterSlider> reverbWetKnob;
    ScopedPointer<ParameterSlider> reverbDryKnob;
    ScopedPointer<ParameterSlider> reverbWidthKnob;
    ScopedPointer<Label> sizeLabel;
    ScopedPointer<Label> dampingLabel;
    ScopedPointer<Label> wetLabel;
    ScopedPointer<Label> dryLabel;
    ScopedPointer<Label> widthLabel;
    ScopedPointer<ToggleButton> reverbToggleButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_F31C8E96463616E__
