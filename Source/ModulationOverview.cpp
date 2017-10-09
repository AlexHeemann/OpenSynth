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
    update();
    setSize(100, 180);
}

ModulationOverview::~ModulationOverview()
{
}

void ModulationOverview::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void ModulationOverview::clear()
{
    modulationPopovers.clear();
    sourceNameLabels.clear();
    removeButtons.clear();
    buttonToSourceMap.clear();
}

void ModulationOverview::update()
{
    for (auto& popover : modulationPopovers)
    {
        popover->removeListener(this);
        removeChildComponent(&*popover);
    }
    for (auto& label : sourceNameLabels)
    {
        removeChildComponent(&*label);
    }
    for (auto& button : removeButtons)
    {
        removeChildComponent(&*button);
    }
    clear();
    
    std::list<int>* sourcesForDestination = processor.getModulationMatrix()->getSourcesForDestination(destinationID);
    if (sourcesForDestination == nullptr) return;
    
    for (std::list<int>::const_iterator iterator = sourcesForDestination->begin(), end = sourcesForDestination->end(); iterator != end; ++iterator)
    {
        std::unique_ptr<ModulationPopover> p(new ModulationPopover());
        p->setSourceID(*iterator);
        p->setSliderValue(processor.getModulationMatrix()->getModulationAmount(*iterator, destinationID));
        p->addListener(this);
        addAndMakeVisible(*p);
        modulationPopovers.push_back(std::move(p));
        
        std::unique_ptr<Label> l(new Label());
        l->setText(String(processor.getModulationMatrix()->getSourceName(*iterator)), NotificationType::dontSendNotification);
        l->setBounds(0, 0, 50, 20);
        l->setColour(Label::ColourIds::textColourId, Colours::white);
        addAndMakeVisible(*l);
        sourceNameLabels.push_back(std::move(l));
        
        std::unique_ptr<DrawableButton> b(new DrawableButton("remove modulation button", DrawableButton::ImageRaw));
        b->setColour(DrawableButton::backgroundColourId, Colours::red);
        b->setBounds(0, 0, 10, 10);
        addAndMakeVisible(*b);
        b->addListener(this);
        buttonToSourceMap[b.get()] = *iterator;
        removeButtons.push_back(std::move(b));
    }
    
    resized();
}

void ModulationOverview::buttonClicked(juce::Button* button)
{
    if (buttonToSourceMap.find(button) != buttonToSourceMap.end())
    {
        processor.getModulationMatrix()->disconnect(buttonToSourceMap[button], destinationID);
        update();
    }
}

void ModulationOverview::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    for (int index = 0; index < modulationPopovers.size(); ++index)
    {
        int popoverWidth = modulationPopovers[index]->getWidth();
        int popoverHeight = modulationPopovers[index]->getHeight();
        modulationPopovers[index]->setTopLeftPosition(5, index * popoverHeight + 10);
        sourceNameLabels[index]->setTopLeftPosition(popoverWidth + 5, index * popoverHeight + 15);
        removeButtons[index]->setTopLeftPosition(popoverWidth + 30, index * popoverHeight + 10);
    }
}

void ModulationOverview::modulationPopoverValueChanged(ModulationPopover* modulationPopover)
{
    processor.updateModulationAmount(modulationPopover->getSourceID(), destinationID, modulationPopover->getModulationAmount());
}

