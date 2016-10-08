/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_AE6DF166ACEDA2F2__
#define __JUCE_HEADER_AE6DF166ACEDA2F2__

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
class OscillatorComponent  : public Component,
                             public ComboBoxListener,
                             public SliderListener
{
public:
    //==============================================================================
    ~OscillatorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    OscillatorComponent(NoisemakerAudioProcessor& processor);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    NoisemakerAudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> osc1ComboBox;
    ScopedPointer<Slider> oscMixSlider;
    ScopedPointer<ComboBox> osc2ComboBox;
    ScopedPointer<ParameterSlider> osc1SemiSlider;
    ScopedPointer<ParameterSlider> osc2SemiSlider2;
    ScopedPointer<Label> mixLabel;
    ScopedPointer<Label> titleLabel;
    ScopedPointer<Label> semi1Label;
    ScopedPointer<Label> semi1Label2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_AE6DF166ACEDA2F2__
