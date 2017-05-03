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

#include "OscillatorComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OscillatorComponent::OscillatorComponent (OscillatorParameterContainer& parameterContainer)
    : parameterContainer(parameterContainer)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible (osc1SemiSlider = new ParameterSlider (*parameterContainer.getOsc1SemiParameter()));
    addAndMakeVisible (osc2SemiSlider = new ParameterSlider (*parameterContainer.getOsc2SemiParameter()));
    addAndMakeVisible (oscMixSlider = new ParameterSlider (*parameterContainer.getOscMixParameter()));
    addAndMakeVisible (osc1CentSlider = new ParameterSlider (*parameterContainer.getOsc1Cents()));
    addAndMakeVisible (osc2CentSlider = new ParameterSlider (*parameterContainer.getOsc2Cents()));
    //[/Constructor_pre]

    addAndMakeVisible (osc1ComboBox = new ComboBox ("Osc 1 Combo Box"));
    osc1ComboBox->setEditableText (false);
    osc1ComboBox->setJustificationType (Justification::centredLeft);
    osc1ComboBox->setTextWhenNothingSelected (TRANS("Waveform"));
    osc1ComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    osc1ComboBox->addItem (TRANS("Sine"), 1);
    osc1ComboBox->addItem (TRANS("Sawtooth"), 2);
    osc1ComboBox->addItem (TRANS("Square"), 3);
    osc1ComboBox->addItem (TRANS("Triangle"), 4);
    osc1ComboBox->addListener (this);

    oscMixSlider->setRange (0, 1, 0);
    oscMixSlider->setSliderStyle (Slider::Rotary);
    oscMixSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    oscMixSlider->setColour (Slider::thumbColourId, Colour (0xff04042a));
    oscMixSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fc30d0d));

    addAndMakeVisible (osc2ComboBox = new ComboBox ("Osc 2 Combo Box"));
    osc2ComboBox->setEditableText (false);
    osc2ComboBox->setJustificationType (Justification::centredLeft);
    osc2ComboBox->setTextWhenNothingSelected (TRANS("Waveform"));
    osc2ComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    osc2ComboBox->addItem (TRANS("Sine"), 1);
    osc2ComboBox->addItem (TRANS("Sawtooth"), 2);
    osc2ComboBox->addItem (TRANS("Square"), 3);
    osc2ComboBox->addItem (TRANS("Triangle"), 4);
    osc2ComboBox->addListener (this);

    addAndMakeVisible (mixLabel = new Label ("Mix Label",
                                             TRANS("Mix")));
    mixLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    mixLabel->setJustificationType (Justification::centredLeft);
    mixLabel->setEditable (false, false, false);
    mixLabel->setColour (Label::textColourId, Colours::black);
    mixLabel->setColour (TextEditor::textColourId, Colours::black);
    mixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (titleLabel = new Label ("Title Label",
                                               TRANS("Oscillators")));
    titleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (Label::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    osc1SemiSlider->setRange (0, 1, 0);
    osc1SemiSlider->setSliderStyle (Slider::LinearHorizontal);
    osc1SemiSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc1SemiSlider->setColour (Slider::trackColourId, Colours::white);

    osc2SemiSlider->setRange (0, 1, 0);
    osc2SemiSlider->setSliderStyle (Slider::LinearHorizontal);
    osc2SemiSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc2SemiSlider->setColour (Slider::trackColourId, Colours::white);

    osc1CentSlider->setRange (0, 1, 0);
    osc1CentSlider->setSliderStyle (Slider::LinearHorizontal);
    osc1CentSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc1CentSlider->setColour (Slider::trackColourId, Colours::white);

    osc2CentSlider->setRange (0, 1, 0);
    osc2CentSlider->setSliderStyle (Slider::LinearHorizontal);
    osc2CentSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc2CentSlider->setColour (Slider::trackColourId, Colours::white);

    addAndMakeVisible (osc1SemiLabel = new Label ("Osc 1 Semi Label",
                                                  TRANS("Semi")));
    osc1SemiLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    osc1SemiLabel->setJustificationType (Justification::centredLeft);
    osc1SemiLabel->setEditable (false, false, false);
    osc1SemiLabel->setColour (TextEditor::textColourId, Colours::black);
    osc1SemiLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (osc1CentsLabel = new Label ("Osc 1 Cents Label",
                                                   TRANS("Cents")));
    osc1CentsLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    osc1CentsLabel->setJustificationType (Justification::centredLeft);
    osc1CentsLabel->setEditable (false, false, false);
    osc1CentsLabel->setColour (TextEditor::textColourId, Colours::black);
    osc1CentsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (osc2SemiLabel = new Label ("Osc 2 Semi Label",
                                                  TRANS("Semi")));
    osc2SemiLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    osc2SemiLabel->setJustificationType (Justification::centredLeft);
    osc2SemiLabel->setEditable (false, false, false);
    osc2SemiLabel->setColour (TextEditor::textColourId, Colours::black);
    osc2SemiLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (osc2CentsLabel = new Label ("Osc 2 Cents Label",
                                                   TRANS("Cents")));
    osc2CentsLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    osc2CentsLabel->setJustificationType (Justification::centredLeft);
    osc2CentsLabel->setEditable (false, false, false);
    osc2CentsLabel->setColour (TextEditor::textColourId, Colours::black);
    osc2CentsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (210, 260);


    //[Constructor] You can add your own custom stuff here..
    osc1ComboBox->setSelectedId(2);
    osc2ComboBox->setSelectedId(2);
    //[/Constructor]
}

OscillatorComponent::~OscillatorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    osc1ComboBox = nullptr;
    oscMixSlider = nullptr;
    osc2ComboBox = nullptr;
    mixLabel = nullptr;
    titleLabel = nullptr;
    osc1SemiSlider = nullptr;
    osc2SemiSlider = nullptr;
    osc1CentSlider = nullptr;
    osc2CentSlider = nullptr;
    osc1SemiLabel = nullptr;
    osc1CentsLabel = nullptr;
    osc2SemiLabel = nullptr;
    osc2CentsLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OscillatorComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xff39bccf));
    g.fillRect (2, 53, 150, 43);

    g.setColour (Colour (0xff10d2ee));
    g.fillRect (2, 93, 150, 43);

    g.setColour (Colour (0xff39bccf));
    g.fillRect (2, 173, 150, 43);

    g.setColour (Colour (0xff10d2ee));
    g.fillRect (2, 213, 150, 43);

    //[UserPaint] Add your own custom painting code here..
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    //[/UserPaint]
}

void OscillatorComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    osc1ComboBox->setBounds (8, 24, 104, 24);
    oscMixSlider->setBounds (160, 8, 48, 48);
    osc2ComboBox->setBounds (8, 144, 104, 24);
    mixLabel->setBounds (168, 48, 32, 24);
    titleLabel->setBounds (24, 0, 79, 24);
    osc1SemiSlider->setBounds (8, 56, 104, 32);
    osc2SemiSlider->setBounds (8, 176, 104, 32);
    osc1CentSlider->setBounds (8, 96, 104, 32);
    osc2CentSlider->setBounds (8, 216, 104, 32);
    osc1SemiLabel->setBounds (112, 56, 40, 24);
    osc1CentsLabel->setBounds (112, 96, 40, 24);
    osc2SemiLabel->setBounds (112, 176, 40, 24);
    osc2CentsLabel->setBounds (112, 216, 40, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OscillatorComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == osc1ComboBox)
    {
        //[UserComboBoxCode_osc1ComboBox] -- add your combo box handling code here..
        parameterContainer.setWaveformForOscillator(waveformForId(comboBoxThatHasChanged->getSelectedId()), 1);
        //[/UserComboBoxCode_osc1ComboBox]
    }
    else if (comboBoxThatHasChanged == osc2ComboBox)
    {
        //[UserComboBoxCode_osc2ComboBox] -- add your combo box handling code here..
        parameterContainer.setWaveformForOscillator(waveformForId(comboBoxThatHasChanged->getSelectedId()), 2);
        //[/UserComboBoxCode_osc2ComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
Waveform OscillatorComponent::waveformForId(int waveformId)
{
    switch (waveformId) {
        case 1:
            return WaveformSine;
        case 2:
            return WaveformSawtooth;
        case 3:
            return WaveformSquare;
        case 4:
            return WaveformTriangle;
        default:
            return WaveformSine;
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OscillatorComponent" componentName=""
                 parentClasses="public Component" constructorParams="OscillatorParameterContainer&amp; parameterContainer"
                 variableInitialisers="parameterContainer(parameterContainer)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="210" initialHeight="260">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="2 53 150 43" fill="solid: ff39bccf" hasStroke="0"/>
    <RECT pos="2 93 150 43" fill="solid: ff10d2ee" hasStroke="0"/>
    <RECT pos="2 173 150 43" fill="solid: ff39bccf" hasStroke="0"/>
    <RECT pos="2 213 150 43" fill="solid: ff10d2ee" hasStroke="0"/>
  </BACKGROUND>
  <COMBOBOX name="Osc 1 Combo Box" id="b7704cccd5f9a10e" memberName="osc1ComboBox"
            virtualName="" explicitFocusOrder="0" pos="8 24 104 24" editable="0"
            layout="33" items="Sine&#10;Sawtooth&#10;Square&#10;Triangle"
            textWhenNonSelected="Waveform" textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc Mix Slider" id="368c17e28bf26c7e" memberName="oscMixSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="160 8 48 48"
          thumbcol="ff04042a" rotarysliderfill="7fc30d0d" min="0" max="1"
          int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="0"/>
  <COMBOBOX name="Osc 2 Combo Box" id="25eaf7f08f3dfc88" memberName="osc2ComboBox"
            virtualName="" explicitFocusOrder="0" pos="8 144 104 24" editable="0"
            layout="33" items="Sine&#10;Sawtooth&#10;Square&#10;Triangle"
            textWhenNonSelected="Waveform" textWhenNoItems="(no choices)"/>
  <LABEL name="Mix Label" id="d01ee9ac72b6cecf" memberName="mixLabel"
         virtualName="" explicitFocusOrder="0" pos="168 48 32 24" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Mix" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Title Label" id="5be71bd636933011" memberName="titleLabel"
         virtualName="" explicitFocusOrder="0" pos="24 0 79 24" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Oscillators" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Osc 1 Semi Slider" id="f2161025490f057a" memberName="osc1SemiSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 56 104 32"
          trackcol="ffffffff" min="0" max="1" int="0" style="LinearHorizontal"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="0"/>
  <SLIDER name="Osc 2 Semi Slider" id="6227ac989c2722d2" memberName="osc2SemiSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 176 104 32"
          trackcol="ffffffff" min="0" max="1" int="0" style="LinearHorizontal"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="0"/>
  <SLIDER name="Osc 1 Cent Slider" id="85eb72c602140d33" memberName="osc1CentSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 96 104 32"
          trackcol="ffffffff" min="0" max="1" int="0" style="LinearHorizontal"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="0"/>
  <SLIDER name="Osc 2 Cent Slider" id="9f37de1daa10a627" memberName="osc2CentSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 216 104 32"
          trackcol="ffffffff" min="0" max="1" int="0" style="LinearHorizontal"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="0"/>
  <LABEL name="Osc 1 Semi Label" id="a15acc2dcec0c75d" memberName="osc1SemiLabel"
         virtualName="" explicitFocusOrder="0" pos="112 56 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Semi" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Osc 1 Cents Label" id="4a616d42488b077f" memberName="osc1CentsLabel"
         virtualName="" explicitFocusOrder="0" pos="112 96 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Cents" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Osc 2 Semi Label" id="b45d0aa1f88a2fce" memberName="osc2SemiLabel"
         virtualName="" explicitFocusOrder="0" pos="112 176 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Semi" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Osc 2 Cents Label" id="e5c6d319c74eba51" memberName="osc2CentsLabel"
         virtualName="" explicitFocusOrder="0" pos="112 216 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Cents" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
