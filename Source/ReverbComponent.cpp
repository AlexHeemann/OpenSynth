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

#include "ReverbComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ReverbComponent::ReverbComponent (ReverbParameterContainer& parameterContainer)
    : parameterContainer(parameterContainer)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible (reverbSizeKnob = new ParameterSlider (*parameterContainer.getReverbSizeParameter()));
    addAndMakeVisible (reverbDampingKnob = new ParameterSlider (*parameterContainer.getReverbDampingParameter()));
    addAndMakeVisible (reverbWetKnob = new ParameterSlider (*parameterContainer.getReverbWetParameter()));
    addAndMakeVisible (reverbDryKnob = new ParameterSlider (*parameterContainer.getReverbDryParameter()));
    addAndMakeVisible (reverbWidthKnob = new ParameterSlider (*parameterContainer.getReverbWidthParameter()));
    //[/Constructor_pre]

    addAndMakeVisible (reverbTitleLabel = new Label ("Reverb Title Label",
                                                     TRANS("Reverb")));
    reverbTitleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    reverbTitleLabel->setJustificationType (Justification::centredLeft);
    reverbTitleLabel->setEditable (false, false, false);
    reverbTitleLabel->setColour (Label::backgroundColourId, Colours::white);
    reverbTitleLabel->setColour (Label::textColourId, Colours::black);
    reverbTitleLabel->setColour (TextEditor::textColourId, Colours::black);
    reverbTitleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    reverbSizeKnob->setRange (0, 1, 0);
    reverbSizeKnob->setSliderStyle (Slider::Rotary);
    reverbSizeKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);

    reverbDampingKnob->setRange (0, 1, 0);
    reverbDampingKnob->setSliderStyle (Slider::Rotary);
    reverbDampingKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);

    reverbWetKnob->setRange (0, 1, 0);
    reverbWetKnob->setSliderStyle (Slider::Rotary);
    reverbWetKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);

    reverbDryKnob->setRange (0, 1, 0);
    reverbDryKnob->setSliderStyle (Slider::Rotary);
    reverbDryKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);

    reverbWidthKnob->setRange (0, 1, 0);
    reverbWidthKnob->setSliderStyle (Slider::Rotary);
    reverbWidthKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);

    addAndMakeVisible (sizeLabel = new Label ("Size Label",
                                              TRANS("Size")));
    sizeLabel->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    sizeLabel->setJustificationType (Justification::centredLeft);
    sizeLabel->setEditable (false, false, false);
    sizeLabel->setColour (Label::textColourId, Colours::black);
    sizeLabel->setColour (TextEditor::textColourId, Colours::black);
    sizeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dampingLabel = new Label ("Damping",
                                                 TRANS("Damping")));
    dampingLabel->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    dampingLabel->setJustificationType (Justification::centredLeft);
    dampingLabel->setEditable (false, false, false);
    dampingLabel->setColour (Label::textColourId, Colours::black);
    dampingLabel->setColour (TextEditor::textColourId, Colours::black);
    dampingLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (wetLabel = new Label ("Wet Label",
                                             TRANS("Wet")));
    wetLabel->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    wetLabel->setJustificationType (Justification::centredLeft);
    wetLabel->setEditable (false, false, false);
    wetLabel->setColour (Label::textColourId, Colours::black);
    wetLabel->setColour (TextEditor::textColourId, Colours::black);
    wetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dryLabel = new Label ("Dry Label",
                                             TRANS("Dry")));
    dryLabel->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    dryLabel->setJustificationType (Justification::centredLeft);
    dryLabel->setEditable (false, false, false);
    dryLabel->setColour (Label::textColourId, Colours::black);
    dryLabel->setColour (TextEditor::textColourId, Colours::black);
    dryLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (widthLabel = new Label ("Width Label",
                                               TRANS("Width")));
    widthLabel->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    widthLabel->setJustificationType (Justification::centredLeft);
    widthLabel->setEditable (false, false, false);
    widthLabel->setColour (Label::textColourId, Colours::black);
    widthLabel->setColour (TextEditor::textColourId, Colours::black);
    widthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (reverbToggleButton = new ToggleButton ("Enabled Toggle Button"));
    reverbToggleButton->setButtonText (String());
    reverbToggleButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (120, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ReverbComponent::~ReverbComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    reverbTitleLabel = nullptr;
    reverbSizeKnob = nullptr;
    reverbDampingKnob = nullptr;
    reverbWetKnob = nullptr;
    reverbDryKnob = nullptr;
    reverbWidthKnob = nullptr;
    sizeLabel = nullptr;
    dampingLabel = nullptr;
    wetLabel = nullptr;
    dryLabel = nullptr;
    widthLabel = nullptr;
    reverbToggleButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ReverbComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::chocolate);
    g.fillRect (0, 0, 120, 24);

    //[UserPaint] Add your own custom painting code here..
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    //[/UserPaint]
}

void ReverbComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    reverbTitleLabel->setBounds (34, 4, 53, 16);
    reverbSizeKnob->setBounds (8, 29, 48, 40);
    reverbDampingKnob->setBounds (64, 29, 48, 40);
    reverbWetKnob->setBounds (8, 88, 48, 40);
    reverbDryKnob->setBounds (64, 88, 48, 40);
    reverbWidthKnob->setBounds (8, 144, 48, 40);
    sizeLabel->setBounds (16, 64, 32, 16);
    dampingLabel->setBounds (59, 64, 59, 16);
    wetLabel->setBounds (16, 124, 31, 14);
    dryLabel->setBounds (72, 125, 31, 13);
    widthLabel->setBounds (13, 179, 40, 16);
    reverbToggleButton->setBounds (6, 0, 98, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ReverbComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == reverbToggleButton)
    {
        //[UserButtonCode_reverbToggleButton] -- add your button handler code here..
        parameterContainer.getReverbEnabledParameter()->setValueNotifyingHost(buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_reverbToggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ReverbComponent" componentName=""
                 parentClasses="public Component" constructorParams="ReverbParameterContainer&amp; parameterContainer"
                 variableInitialisers="parameterContainer(parameterContainer)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="120" initialHeight="200">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 120 24" fill="solid: ffd2691e" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="Reverb Title Label" id="22a399ed1ffe13ed" memberName="reverbTitleLabel"
         virtualName="" explicitFocusOrder="0" pos="34 4 53 16" bkgCol="ffffffff"
         textCol="ff000000" edTextCol="ff000000" edBkgCol="0" labelText="Reverb"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
         justification="33"/>
  <SLIDER name="Reverb Size Knob" id="5d03a43546f16b0c" memberName="reverbSizeKnob"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 29 48 40"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Reverb Damping Knob" id="ecdb649a28f7ae4a" memberName="reverbDampingKnob"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="64 29 48 40"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Reverb Wet Knob" id="2a8fd0bbf6143a9" memberName="reverbWetKnob"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 88 48 40"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Reverb Dry Knob" id="eb94a868ca3f79c0" memberName="reverbDryKnob"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="64 88 48 40"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Reverb Width Knob" id="4472b5792035d16d" memberName="reverbWidthKnob"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 144 48 40"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <LABEL name="Size Label" id="da35f56642f1beea" memberName="sizeLabel"
         virtualName="" explicitFocusOrder="0" pos="16 64 32 16" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Size" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Damping" id="6e140bedf24f8ed6" memberName="dampingLabel"
         virtualName="" explicitFocusOrder="0" pos="59 64 59 16" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Damping" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Wet Label" id="7532d935b4e82b81" memberName="wetLabel"
         virtualName="" explicitFocusOrder="0" pos="16 124 31 14" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Wet" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Dry Label" id="60f7cd654e6f045d" memberName="dryLabel"
         virtualName="" explicitFocusOrder="0" pos="72 125 31 13" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Dry" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Width Label" id="ddc79248f2583b8c" memberName="widthLabel"
         virtualName="" explicitFocusOrder="0" pos="13 179 40 16" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Width" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" kerning="0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="Enabled Toggle Button" id="57b1784b8a594edf" memberName="reverbToggleButton"
                virtualName="" explicitFocusOrder="0" pos="6 0 98 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
