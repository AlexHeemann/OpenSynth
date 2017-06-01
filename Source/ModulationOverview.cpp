/*
  ==============================================================================

    ModulationOverview.cpp
    Created: 10 May 2017 8:51:55pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ModulationOverview.h"
#include "ModulationMatrix.h"

//==============================================================================
ModulationOverview::ModulationOverview(int destinationID, OpenSynthAudioProcessor& processor) : destinationID(destinationID), processor(processor)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    update();
    setSize(80, 180);
}

ModulationOverview::~ModulationOverview()
{
}

void ModulationOverview::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void ModulationOverview::update()
{
    for (auto& popover : modulationPopovers)
    {
        removeChildComponent(&*popover);
    }
    modulationPopovers.clear();
    std::list<int>* sources = processor.getModulationMatrix()->getSourcesForDestination(destinationID);
    if (sources != nullptr)
    {
        for (std::list<int>::const_iterator iterator = sources->begin(), end = sources->end(); iterator != end; ++iterator)
        {
            std::unique_ptr<ModulationPopover> p(new ModulationPopover());
            p->setSourceID(*iterator);
            addAndMakeVisible(*p);
            
            modulationPopovers.push_back(std::move(p));
        }
    }
}

void ModulationOverview::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    for (int index = 0; index < modulationPopovers.size(); ++index)
    {
        modulationPopovers[index]->setTopLeftPosition(0, index * modulationPopovers[index]->getHeight() + 5);
    }
}
