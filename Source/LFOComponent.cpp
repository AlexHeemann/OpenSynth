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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "LFOComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LFOComponent::LFOComponent (LFOParameterContainer& parameterContainer)
    : parameterContainer(parameterContainer)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible (frequencySlider = new ParameterSlider (*parameterContainer.getFrequencyParameter()));
    //[/Constructor_pre]

    addAndMakeVisible (lfoTitleLabel = new Label ("LFO Title Label",
                                                  TRANS("LFO")));
    lfoTitleLabel->setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Regular"));
    lfoTitleLabel->setJustificationType (Justification::centredLeft);
    lfoTitleLabel->setEditable (false, false, false);
    lfoTitleLabel->setColour (Label::backgroundColourId, Colour (0xffd05555));
    lfoTitleLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoTitleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    frequencySlider->setRange (0, 1, 0);
    frequencySlider->setSliderStyle (Slider::Rotary);
    frequencySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Frequency\n")));
    label->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::black);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (140, 100);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

LFOComponent::~LFOComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lfoTitleLabel = nullptr;
    frequencySlider = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LFOComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LFOComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    lfoTitleLabel->setBounds (0, 0, 144, 24);
    frequencySlider->setBounds (1, 26, 55, 56);
    label->setBounds (0, 72, 72, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LFOComponent" componentName=""
                 parentClasses="public Component" constructorParams="LFOParameterContainer&amp; parameterContainer"
                 variableInitialisers="parameterContainer(parameterContainer)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="140" initialHeight="100">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="LFO Title Label" id="d57d9b5342a6dbf8" memberName="lfoTitleLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 144 24" bkgCol="ffd05555"
         edTextCol="ff000000" edBkgCol="0" labelText="LFO" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="LFO Frequency Slider" id="11528b7f3ccd952" memberName="frequencySlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="1 26 55 56"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <LABEL name="new label" id="d745b67132d73127" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 72 72 24" textCol="ff000000" edTextCol="ff000000"
         edBkgCol="0" labelText="Frequency&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" kerning="0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
