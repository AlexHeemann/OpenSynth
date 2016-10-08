/*
  ==============================================================================

    ModulationConnector.cpp
    Created: 19 Jun 2016 12:44:18pm
    Author:  Alex

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ModulationConnector.h"

//==============================================================================
ModulationConnector::ModulationConnector()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ModulationConnector::~ModulationConnector()
{
}

void ModulationConnector::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("ModulationConnector", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void ModulationConnector::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

uint32 ModulationConnector::getModulationId()
{
	return this->modulationId;
}

void ModulationConnector::setModulationId(uint32 modulationId)
{
	this->modulationId = modulationId;
}

void ModulationConnector::mouseDown(const juce::MouseEvent & event)
{
}

void ModulationConnector::mouseDrag(const MouseEvent & event)
{
	DragAndDropContainer* container =  DragAndDropContainer::findParentDragContainerFor(this);
	if (container != nullptr)
	{
		container->startDragging(int(modulationId), this);
	}
}
