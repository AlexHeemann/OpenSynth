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

#include "ModulationPopover.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ModulationPopover::ModulationPopover ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (modulationAmountSlider = new Slider ("Modulation Amount Slider"));
    modulationAmountSlider->setRange (0, 1, 0);
    modulationAmountSlider->setSliderStyle (Slider::Rotary);
    modulationAmountSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    modulationAmountSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (50, 50);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ModulationPopover::~ModulationPopover()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    modulationAmountSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ModulationPopover::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff2a40c7));
    g.fillRoundedRectangle (0.0f, 0.0f, 48.0f, 48.0f, 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ModulationPopover::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    modulationAmountSlider->setBounds (0, 0, 48, 48);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ModulationPopover::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == modulationAmountSlider)
    {
        //[UserSliderCode_modulationAmountSlider] -- add your slider handling code here..
        listeners.call (&ModulationPopover::Listener::modulationPopoverValueChanged, this);
        //[/UserSliderCode_modulationAmountSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ModulationPopover::addListener (Listener *const listener)
{
    listeners.add(listener);
}

void ModulationPopover::removeListener(ModulationPopover::Listener *const listener)
{
    listeners.remove(listener);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ModulationPopover" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="50" initialHeight="50">
  <BACKGROUND backgroundColour="ffffff">
    <ROUNDRECT pos="0 0 48 48" cornerSize="10" fill="solid: ff2a40c7" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="Modulation Amount Slider" id="c78256a929d8bac7" memberName="modulationAmountSlider"
          virtualName="Slider" explicitFocusOrder="0" pos="0 0 48 48" min="0"
          max="1" int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
