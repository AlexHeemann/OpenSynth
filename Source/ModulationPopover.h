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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ModulationPopover  : public Component,
                           public SliderListener
{
public:
    //==============================================================================
    ModulationPopover ();
    ~ModulationPopover();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void modulationPopoverValueChanged(ModulationPopover* modulationPopover) = 0;
    };
    
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void setSourceID(int sourceID) { this->sourceID = sourceID; }
    int getSourceID() const { return sourceID; }
    float getModulationAmount() const { return modulationAmountSlider->getValue(); }
    
    /** Adds a listener to be called when this slider's value changes. */
    void addListener (Listener *const listener);
    
    /** Removes a previously-registered listener. */
    void removeListener (Listener *const listener);
    
private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ListenerList<ModulationPopover::Listener> listeners;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> modulationAmountSlider;
    int sourceID;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationPopover)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
