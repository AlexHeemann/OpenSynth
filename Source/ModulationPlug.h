/*
  ==============================================================================

    ModulationPlug.h
    Created: 6 May 2017 2:05:00pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ModulationPlug    : public Component
{
public:
    ModulationPlug();
    ~ModulationPlug();

    void paint (Graphics&) override;
    void resized() override;
    
    virtual void mouseDown(const juce::MouseEvent & event) override;
    virtual void mouseDrag(const MouseEvent& event) override;
    
    void setID(int ID) { this->ID = ID; }
    int getID() { return ID; }

private:
    int ID = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationPlug)
};
