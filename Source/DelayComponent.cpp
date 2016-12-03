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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "DelayComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DelayComponent::DelayComponent (OpenSynthAudioProcessor& processor)
    : processor(processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible(timeKnob = new ParameterSlider(*processor.delayTime));
    addAndMakeVisible (feedKnob = new ParameterSlider (*processor.delayFeedback));
    addAndMakeVisible (spreadKnob = new ParameterSlider (*processor.delaySpread));
    addAndMakeVisible (mixKnob = new ParameterSlider (*processor.delayMix));
    //[/Constructor_pre]

    timeKnob->setRange (0, 1, 0);
    timeKnob->setSliderStyle (Slider::Rotary);
    timeKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    timeKnob->addListener (this);

    feedKnob->setRange (0, 1, 0);
    feedKnob->setSliderStyle (Slider::Rotary);
    feedKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    feedKnob->addListener (this);

    spreadKnob->setRange (0, 1, 0);
    spreadKnob->setSliderStyle (Slider::Rotary);
    spreadKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    spreadKnob->addListener (this);

    mixKnob->setRange (0, 1, 0);
    mixKnob->setSliderStyle (Slider::Rotary);
    mixKnob->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    mixKnob->addListener (this);

    addAndMakeVisible (timeLabel = new Label ("Time Label",
                                              TRANS("Time")));
    timeLabel->setFont (Font (15.00f, Font::plain));
    timeLabel->setJustificationType (Justification::centredLeft);
    timeLabel->setEditable (false, false, false);
    timeLabel->setColour (TextEditor::textColourId, Colours::black);
    timeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (feedLabel = new Label ("Feed Label",
                                              TRANS("Feed")));
    feedLabel->setFont (Font (15.00f, Font::plain));
    feedLabel->setJustificationType (Justification::centredLeft);
    feedLabel->setEditable (false, false, false);
    feedLabel->setColour (TextEditor::textColourId, Colours::black);
    feedLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (spreadLabel = new Label ("Spread Label",
                                                TRANS("Spread")));
    spreadLabel->setFont (Font (15.00f, Font::plain));
    spreadLabel->setJustificationType (Justification::centredLeft);
    spreadLabel->setEditable (false, false, false);
    spreadLabel->setColour (TextEditor::textColourId, Colours::black);
    spreadLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mixLabel = new Label ("Mix Label",
                                             TRANS("Mix")));
    mixLabel->setFont (Font (15.00f, Font::plain));
    mixLabel->setJustificationType (Justification::centredLeft);
    mixLabel->setEditable (false, false, false);
    mixLabel->setColour (TextEditor::textColourId, Colours::black);
    mixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayTitleLabel = new Label ("Delay Title Label",
                                                    TRANS("Delay")));
    delayTitleLabel->setFont (Font (15.00f, Font::plain));
    delayTitleLabel->setJustificationType (Justification::centredLeft);
    delayTitleLabel->setEditable (false, false, false);
    delayTitleLabel->setColour (Label::backgroundColourId, Colours::white);
    delayTitleLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    delayTitleLabel->setColour (TextEditor::textColourId, Colours::black);
    delayTitleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayToggleButton = new ToggleButton ("Delay Toggle Button"));
    delayToggleButton->setButtonText (String());
    delayToggleButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (120, 85);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

DelayComponent::~DelayComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    timeKnob = nullptr;
    feedKnob = nullptr;
    spreadKnob = nullptr;
    mixKnob = nullptr;
    timeLabel = nullptr;
    feedLabel = nullptr;
    spreadLabel = nullptr;
    mixLabel = nullptr;
    delayTitleLabel = nullptr;
    delayToggleButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DelayComponent::paint (Graphics& g)
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

void DelayComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    timeKnob->setBounds (8, 24, 40, 40);
    feedKnob->setBounds (72, 24, 40, 40);
    spreadKnob->setBounds (8, 88, 40, 40);
    mixKnob->setBounds (72, 88, 40, 40);
    timeLabel->setBounds (8, 64, 40, 16);
    feedLabel->setBounds (72, 64, 40, 16);
    spreadLabel->setBounds (0, 128, 56, 16);
    mixLabel->setBounds (75, 128, 32, 16);
    delayTitleLabel->setBounds (38, 4, 48, 16);
    delayToggleButton->setBounds (8, 0, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void DelayComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == timeKnob)
    {
        //[UserSliderCode_timeKnob] -- add your slider handling code here..
        //[/UserSliderCode_timeKnob]
    }
    else if (sliderThatWasMoved == feedKnob)
    {
        //[UserSliderCode_feedKnob] -- add your slider handling code here..
        //[/UserSliderCode_feedKnob]
    }
    else if (sliderThatWasMoved == spreadKnob)
    {
        //[UserSliderCode_spreadKnob] -- add your slider handling code here..
        //[/UserSliderCode_spreadKnob]
    }
    else if (sliderThatWasMoved == mixKnob)
    {
        //[UserSliderCode_mixKnob] -- add your slider handling code here..
        //[/UserSliderCode_mixKnob]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void DelayComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == delayToggleButton)
    {
        //[UserButtonCode_delayToggleButton] -- add your button handler code here..
        processor.delayEnabled->setValueNotifyingHost(buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_delayToggleButton]
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

<JUCER_COMPONENT documentType="Component" className="DelayComponent" componentName=""
                 parentClasses="public Component" constructorParams="OpenSynthAudioProcessor&amp; processor"
                 variableInitialisers="processor(processor)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="120"
                 initialHeight="85">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 120 24" fill="solid: ffd2691e" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="Time Knob" id="aa80732c9a3bcd4b" memberName="timeKnob"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 24 40 40"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Feed Knob" id="84e5b64d59972127" memberName="feedKnob"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="72 24 40 40"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Spread Knob" id="d2b73a7e70853c6d" memberName="spreadKnob"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 88 40 40"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Mix Knob" id="c5bbe7b00c0bec5a" memberName="mixKnob" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="72 88 40 40" min="0" max="1" int="0"
          style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="Time Label" id="38b196fc8a7c0f5f" memberName="timeLabel"
         virtualName="" explicitFocusOrder="0" pos="8 64 40 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Time" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Feed Label" id="bae9c7ca1e0ff466" memberName="feedLabel"
         virtualName="" explicitFocusOrder="0" pos="72 64 40 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Feed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Spread Label" id="34727334d9a5d622" memberName="spreadLabel"
         virtualName="" explicitFocusOrder="0" pos="0 128 56 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Spread" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Mix Label" id="a426f00524c2dd8e" memberName="mixLabel"
         virtualName="" explicitFocusOrder="0" pos="75 128 32 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Mix" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Delay Title Label" id="1aef2ce4beb9bc42" memberName="delayTitleLabel"
         virtualName="" explicitFocusOrder="0" pos="38 4 48 16" bkgCol="ffffffff"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="Delay"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="Delay Toggle Button" id="8f4c7bd269ee1c38" memberName="delayToggleButton"
                virtualName="" explicitFocusOrder="0" pos="8 0 150 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
