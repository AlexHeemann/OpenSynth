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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "EnvelopeComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
EnvelopeComponent::EnvelopeComponent (EnvelopeParameterContainer& parameterContainer)
    : parameterContainer(parameterContainer)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible (attackSlider = new ParameterSlider (*parameterContainer.getAttackRateParameter(), ParameterIDEnvelope1Attack));
    addAndMakeVisible (decaySlider = new ParameterSlider (*parameterContainer.getDecayRateParameter(), ParameterIDEnvelope1Decay));
    addAndMakeVisible (sustainSlider = new ParameterSlider (*parameterContainer.getSustainLevelParameter(), ParameterIDEnvelope1Sustain));
    addAndMakeVisible (releaseSlider = new ParameterSlider (*parameterContainer.getReleaseRateParameter(), ParameterIDEnvelope1Release));
    //[/Constructor_pre]

    addAndMakeVisible (envelopeTitleLabel = new Label ("Envelope Title Label",
                                                       TRANS("Envelope")));
    envelopeTitleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    envelopeTitleLabel->setJustificationType (Justification::centredLeft);
    envelopeTitleLabel->setEditable (false, false, false);
    envelopeTitleLabel->setColour (Label::backgroundColourId, Colour (0xffd05555));
    envelopeTitleLabel->setColour (TextEditor::textColourId, Colours::black);
    envelopeTitleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    attackSlider->setRange (0, 1, 0);
    attackSlider->setSliderStyle (Slider::LinearVertical);
    attackSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    attackSlider->addListener (this);
    
    decaySlider->setRange (0, 1, 0);
    decaySlider->setSliderStyle (Slider::LinearVertical);
    decaySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    decaySlider->addListener (this);
    
    sustainSlider->setRange (0, 1, 0);
    sustainSlider->setSliderStyle (Slider::LinearVertical);
    sustainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sustainSlider->addListener (this);
    
    releaseSlider->setRange (0, 1, 0);
    releaseSlider->setSliderStyle (Slider::LinearVertical);
    releaseSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    releaseSlider->addListener (this);

    addAndMakeVisible (attackLabel = new Label ("Attack Label",
                                                TRANS("A")));
    attackLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    attackLabel->setJustificationType (Justification::centredLeft);
    attackLabel->setEditable (false, false, false);
    attackLabel->setColour (Label::textColourId, Colours::black);
    attackLabel->setColour (TextEditor::textColourId, Colours::black);
    attackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (decayLabel = new Label ("Decay Label",
                                               TRANS("D")));
    decayLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    decayLabel->setJustificationType (Justification::centredLeft);
    decayLabel->setEditable (false, false, false);
    decayLabel->setColour (Label::textColourId, Colours::black);
    decayLabel->setColour (TextEditor::textColourId, Colours::black);
    decayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sustainLabel = new Label ("Sustain Label",
                                                 TRANS("S")));
    sustainLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    sustainLabel->setJustificationType (Justification::centredLeft);
    sustainLabel->setEditable (false, false, false);
    sustainLabel->setColour (Label::textColourId, Colours::black);
    sustainLabel->setColour (TextEditor::textColourId, Colours::black);
    sustainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (releaseLabel = new Label ("Release Label",
                                                 TRANS("R")));
    releaseLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    releaseLabel->setJustificationType (Justification::centredLeft);
    releaseLabel->setEditable (false, false, false);
    releaseLabel->setColour (Label::textColourId, Colours::black);
    releaseLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (modulationPlug = new ModulationPlug());
    modulationPlug->setName ("Modulation Plug");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (180, 120);


    //[Constructor] You can add your own custom stuff here..
    modulationPlug->setID(parameterContainer.getID());
    //[/Constructor]
}

EnvelopeComponent::~EnvelopeComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    envelopeTitleLabel = nullptr;
    attackSlider = nullptr;
    decaySlider = nullptr;
    sustainSlider = nullptr;
    releaseSlider = nullptr;
    attackLabel = nullptr;
    decayLabel = nullptr;
    sustainLabel = nullptr;
    releaseLabel = nullptr;
    modulationPlug = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EnvelopeComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void EnvelopeComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    envelopeTitleLabel->setBounds (0, 0, 184, 24);
    attackSlider->setBounds (8, 24, 24, 80);
    decaySlider->setBounds (40, 24, 24, 80);
    sustainSlider->setBounds (72, 24, 24, 80);
    releaseSlider->setBounds (104, 24, 24, 80);
    attackLabel->setBounds (11, 104, 24, 16);
    decayLabel->setBounds (42, 104, 24, 16);
    sustainLabel->setBounds (75, 104, 24, 16);
    releaseLabel->setBounds (107, 104, 24, 16);
    modulationPlug->setBounds (144, 32, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EnvelopeComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attackSlider)
    {
        //[UserSliderCode_attackSlider] -- add your slider handling code here..
        //[/UserSliderCode_attackSlider]
    }
    else if (sliderThatWasMoved == decaySlider)
    {
        //[UserSliderCode_decaySlider] -- add your slider handling code here..
        //[/UserSliderCode_decaySlider]
    }
    else if (sliderThatWasMoved == sustainSlider)
    {
        //[UserSliderCode_sustainSlider] -- add your slider handling code here..
        //[/UserSliderCode_sustainSlider]
    }
    else if (sliderThatWasMoved == releaseSlider)
    {
        //[UserSliderCode_releaseSlider] -- add your slider handling code here..
        //[/UserSliderCode_releaseSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="EnvelopeComponent" componentName=""
                 parentClasses="public Component" constructorParams="EnvelopeParameterContainer&amp; parameterContainer"
                 variableInitialisers="parameterContainer(parameterContainer)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="180" initialHeight="120">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="Envelope Title Label" id="f2d3f5b60cbdea82" memberName="envelopeTitleLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 184 24" bkgCol="ffd05555"
         edTextCol="ff000000" edBkgCol="0" labelText="Envelope" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Attack Slider" id="fd01b177f9465608" memberName="attackSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 24 24 80"
          min="0" max="1" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Decay Slider" id="339df0236cfccabd" memberName="decaySlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="40 24 24 80"
          min="0" max="1" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Sustain Slider" id="a483e248fcdbd73a" memberName="sustainSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="72 24 24 80"
          min="0" max="1" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Release Slider" id="271e800c065d9f0b" memberName="releaseSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="104 24 24 80"
          min="0" max="1" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="Attack Label" id="994536437479b8f7" memberName="attackLabel"
         virtualName="" explicitFocusOrder="0" pos="11 104 24 16" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="A" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Decay Label" id="66955cd49b4b7131" memberName="decayLabel"
         virtualName="" explicitFocusOrder="0" pos="42 104 24 16" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="D" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Sustain Label" id="4231b6fef05d091e" memberName="sustainLabel"
         virtualName="" explicitFocusOrder="0" pos="75 104 24 16" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="S" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Release Label" id="f786e81cae10fbf8" memberName="releaseLabel"
         virtualName="" explicitFocusOrder="0" pos="107 104 24 16" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Modulation Plug" id="d007b8d447a42d8f" memberName="modulationPlug"
                    virtualName="ModulationPlug" explicitFocusOrder="0" pos="144 32 24 24"
                    class="Component" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
