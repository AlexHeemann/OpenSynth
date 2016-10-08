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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "OscillatorComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OscillatorComponent::OscillatorComponent (NoisemakerAudioProcessor& processor)
    : processor(processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible (osc1SemiSlider = new ParameterSlider (*processor.osc1Semi));
    addAndMakeVisible (osc2SemiSlider = new ParameterSlider (*processor.osc2Semi));
    addAndMakeVisible (oscMixSlider = new ParameterSlider (*processor.oscMix));
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
                                             TRANS("MIx")));
    mixLabel->setFont (Font (15.00f, Font::plain));
    mixLabel->setJustificationType (Justification::centredLeft);
    mixLabel->setEditable (false, false, false);
    mixLabel->setColour (TextEditor::textColourId, Colours::black);
    mixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (titleLabel = new Label ("Title Label",
                                               TRANS("Oscillators")));
    titleLabel->setFont (Font (15.00f, Font::plain));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    osc1SemiSlider->setRange (0, 1, 0);
    osc1SemiSlider->setSliderStyle (Slider::LinearHorizontal);
    osc1SemiSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc1SemiSlider->addListener (this);

    osc2SemiSlider->setRange (0, 1, 0);
    osc2SemiSlider->setSliderStyle (Slider::LinearHorizontal);
    osc2SemiSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    osc2SemiSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (190, 180);


    //[Constructor] You can add your own custom stuff here..
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


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OscillatorComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

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
    oscMixSlider->setBounds (128, 8, 48, 48);
    osc2ComboBox->setBounds (8, 104, 104, 24);
    mixLabel->setBounds (136, 56, 32, 24);
    titleLabel->setBounds (24, 0, 79, 24);
    osc1SemiSlider->setBounds (8, 56, 104, 32);
    osc2SemiSlider->setBounds (8, 136, 104, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

Waveform OscillatorComponent::waveformForId(int waveformId)
{
    switch (waveformId)
    {
        case 1:
            return WaveformSine;
        case 2:
            return WaveformSawtooth;
        case 3:
            return WaveformSquare;
        case 4:
            return WaveformSine;
        default:
            return  WaveformSine;
    }
}

void OscillatorComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == osc1ComboBox)
    {
        //[UserComboBoxCode_osc1ComboBox] -- add your combo box handling code here..
        processor.setWaveformForOscillator(waveformForId(comboBoxThatHasChanged->getSelectedId()), 1);
        //[/UserComboBoxCode_osc1ComboBox]
    }
    else if (comboBoxThatHasChanged == osc2ComboBox)
    {
        //[UserComboBoxCode_osc2ComboBox] -- add your combo box handling code here..
        processor.setWaveformForOscillator(waveformForId(comboBoxThatHasChanged->getSelectedId()), 2);
        //[/UserComboBoxCode_osc2ComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void OscillatorComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == osc1SemiSlider)
    {
        //[UserSliderCode_osc1SemiSlider] -- add your slider handling code here..
        //[/UserSliderCode_osc1SemiSlider]
    }
    else if (sliderThatWasMoved == osc2SemiSlider)
    {
        //[UserSliderCode_osc2SemiSlider] -- add your slider handling code here..
        //[/UserSliderCode_osc2SemiSlider]
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

<JUCER_COMPONENT documentType="Component" className="OscillatorComponent" componentName=""
                 parentClasses="public Component" constructorParams="NoisemakerAudioProcessor&amp; processor"
                 variableInitialisers="processor(processor)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="190"
                 initialHeight="180">
  <BACKGROUND backgroundColour="ffffffff"/>
  <COMBOBOX name="Osc 1 Combo Box" id="b7704cccd5f9a10e" memberName="osc1ComboBox"
            virtualName="" explicitFocusOrder="0" pos="8 24 104 24" editable="0"
            layout="33" items="Sine&#10;Sawtooth&#10;Square&#10;Triangle"
            textWhenNonSelected="Waveform" textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc Mix Slider" id="368c17e28bf26c7e" memberName="oscMixSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="128 8 48 48"
          thumbcol="ff04042a" rotarysliderfill="7fc30d0d" min="0" max="1"
          int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="0"/>
  <COMBOBOX name="Osc 2 Combo Box" id="25eaf7f08f3dfc88" memberName="osc2ComboBox"
            virtualName="" explicitFocusOrder="0" pos="8 104 104 24" editable="0"
            layout="33" items="Sine&#10;Sawtooth&#10;Square&#10;Triangle"
            textWhenNonSelected="Waveform" textWhenNoItems="(no choices)"/>
  <LABEL name="Mix Label" id="d01ee9ac72b6cecf" memberName="mixLabel"
         virtualName="" explicitFocusOrder="0" pos="136 56 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="MIx" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Title Label" id="5be71bd636933011" memberName="titleLabel"
         virtualName="" explicitFocusOrder="0" pos="24 0 79 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Oscillators" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="Osc 1 Semi Slider" id="f2161025490f057a" memberName="osc1SemiSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 56 104 32"
          min="0" max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Osc 2 Semi Slider" id="6227ac989c2722d2" memberName="osc2SemiSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 136 104 32"
          min="0" max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
