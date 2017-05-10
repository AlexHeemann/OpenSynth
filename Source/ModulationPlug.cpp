/*
  ==============================================================================

    ModulationPlug.cpp
    Created: 6 May 2017 2:05:00pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ModulationPlug.h"

//==============================================================================
ModulationPlug::ModulationPlug()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ModulationPlug::~ModulationPlug()
{
}

void ModulationPlug::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
}

void ModulationPlug::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void ModulationPlug::mouseDown(const juce::MouseEvent & event)
{
}

void ModulationPlug::mouseDrag(const MouseEvent & event)
{
    DragAndDropContainer* container = juce::DragAndDropContainer::findParentDragContainerFor(this);
    if (container != nullptr)
    {
        container->startDragging(ID, this);
    }
}
