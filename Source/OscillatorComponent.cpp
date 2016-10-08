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
OscillatorComponent::OscillatorComponent (NoisemakerAudioProcessor& processor) : processor(processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible (osc1SemiSlider = new ParameterSlider (*processor.osc1Semi));
    osc1SemiSlider->setRange (-36, 36, 1);
    osc1SemiSlider->setSliderStyle (Slider::LinearHorizontal);
    osc1SemiSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    osc1SemiSlider->addListener (this);
    
    addAndMakeVisible (osc2SemiSlider2 = new ParameterSlider (*processor.osc2Semi));
    osc2SemiSlider2->setRange (-36, 36, 1);
    osc2SemiSlider2->setSliderStyle (Slider::LinearHorizontal);
    osc2SemiSlider2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    osc2SemiSlider2->addListener (this);
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

    addAndMakeVisible (oscMixSlider = new Slider ("Osc Mix Slider"));
    oscMixSlider->setRange (0, 10, 0);
    oscMixSlider->setSliderStyle (Slider::Rotary);
    oscMixSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    oscMixSlider->setColour (Slider::thumbColourId, Colour (0xff04042a));
    oscMixSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    oscMixSlider->addListener (this);

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

    addAndMakeVisible (semi1Label = new Label ("Semi 1 Label",
                                               TRANS("Semi")));
    semi1Label->setFont (Font (15.00f, Font::plain));
    semi1Label->setJustificationType (Justification::centredLeft);
    semi1Label->setEditable (false, false, false);
    semi1Label->setColour (TextEditor::textColourId, Colours::black);
    semi1Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (semi1Label2 = new Label ("Semi 1 Label",
                                                TRANS("Semi")));
    semi1Label2->setFont (Font (15.00f, Font::plain));
    semi1Label2->setJustificationType (Justification::centredLeft);
    semi1Label2->setEditable (false, false, false);
    semi1Label2->setColour (TextEditor::textColourId, Colours::black);
    semi1Label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


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
    osc1SemiSlider = nullptr;
    osc2SemiSlider2 = nullptr;
    mixLabel = nullptr;
    titleLabel = nullptr;
    semi1Label = nullptr;
    semi1Label2 = nullptr;


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
    //[/UserPaint]
}

void OscillatorComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    osc1ComboBox->setBounds (8, 32, 104, 24);
    oscMixSlider->setBounds (128, 8, 48, 48);
    osc2ComboBox->setBounds (8, 112, 104, 24);
    osc1SemiSlider->setBounds (8, 56, 104, 24);
    osc2SemiSlider2->setBounds (8, 136, 104, 24);
    mixLabel->setBounds (136, 56, 32, 24);
    titleLabel->setBounds (24, 0, 79, 24);
    semi1Label->setBounds (40, 72, 40, 24);
    semi1Label2->setBounds (40, 152, 40, 24);
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
        //[/UserComboBoxCode_osc1ComboBox]
    }
    else if (comboBoxThatHasChanged == osc2ComboBox)
    {
        //[UserComboBoxCode_osc2ComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_osc2ComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void OscillatorComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == oscMixSlider)
    {
        //[UserSliderCode_oscMixSlider] -- add your slider handling code here..
        //[/UserSliderCode_oscMixSlider]
    }
    else if (sliderThatWasMoved == osc1SemiSlider)
    {
        //[UserSliderCode_osc1SemiSlider] -- add your slider handling code here..
        //[/UserSliderCode_osc1SemiSlider]
    }
    else if (sliderThatWasMoved == osc2SemiSlider2)
    {
        //[UserSliderCode_osc2SemiSlider2] -- add your slider handling code here..
        //[/UserSliderCode_osc2SemiSlider2]
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
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="190" initialHeight="180">
  <BACKGROUND backgroundColour="ffffffff"/>
  <COMBOBOX name="Osc 1 Combo Box" id="b7704cccd5f9a10e" memberName="osc1ComboBox"
            virtualName="" explicitFocusOrder="0" pos="8 32 104 24" editable="0"
            layout="33" items="Sine&#10;Sawtooth&#10;Square&#10;Triangle"
            textWhenNonSelected="Waveform" textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc Mix Slider" id="368c17e28bf26c7e" memberName="oscMixSlider"
          virtualName="" explicitFocusOrder="0" pos="128 8 48 48" thumbcol="ff04042a"
          rotarysliderfill="7fffffff" min="0" max="10" int="0" style="Rotary"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <COMBOBOX name="Osc 2 Combo Box" id="25eaf7f08f3dfc88" memberName="osc2ComboBox"
            virtualName="" explicitFocusOrder="0" pos="8 112 104 24" editable="0"
            layout="33" items="Sine&#10;Sawtooth&#10;Square&#10;Triangle"
            textWhenNonSelected="Waveform" textWhenNoItems="(no choices)"/>
  <SLIDER name="Osc 1 Semi Slider" id="1dc6244e1f58287a" memberName="osc1SemiSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 56 104 24"
          min="-36" max="36" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Osc 2 Semi Slider" id="6529e888544d35fc" memberName="osc2SemiSlider2"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="8 136 104 24"
          min="-36" max="36" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
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
  <LABEL name="Semi 1 Label" id="fab534ab38557660" memberName="semi1Label"
         virtualName="" explicitFocusOrder="0" pos="40 72 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Semi" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Semi 1 Label" id="44fa240960091078" memberName="semi1Label2"
         virtualName="" explicitFocusOrder="0" pos="40 152 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Semi" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
