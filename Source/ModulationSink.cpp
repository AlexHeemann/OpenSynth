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

#include "ModulationSink.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ModulationSink::ModulationSink ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (titleLabel = new Label ("Title Label",
                                               TRANS("M")));
    titleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (Label::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (20, 20);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

void ModulationSink::setHighlighted(bool highlighted)
{
    isHighlighted = highlighted;
    repaint();
}

ModulationSink::~ModulationSink()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    titleLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ModulationSink::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    if (isHighlighted)
    {
        g.setColour(Colour(0, 200, 23));
    }
    else
    {
        g.setColour (Colour (0xff2aa5a5));
    }
    g.fillRoundedRectangle (0.0f, 0.0f, 20.0f, 20.0f, 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ModulationSink::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    titleLabel->setBounds (-1, 2, 24, 16);
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

<JUCER_COMPONENT documentType="Component" className="ModulationSink" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="20" initialHeight="20">
  <BACKGROUND backgroundColour="ffffff">
    <ROUNDRECT pos="0 0 20 20" cornerSize="10" fill="solid: ff2aa5a5" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="Title Label" id="a57bb9e85a3f23a2" memberName="titleLabel"
         virtualName="" explicitFocusOrder="0" pos="-1 2 24 16" textCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="M" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
