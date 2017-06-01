/*
  ==============================================================================

    ModulatedComponent.cpp
    Created: 10 May 2017 1:26:18pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ModulatedComponent.h"

//==============================================================================
ModulatedComponent::ModulatedComponent(AudioProcessorParameter& p, int ID) : Module(ID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(slider = new ParameterSlider(p, ID));
    addAndMakeVisible(modulationSink = new ModulationSink());
}

ModulatedComponent::~ModulatedComponent()
{
}

void ModulatedComponent::paint (Graphics& g)
{
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void ModulatedComponent::resized()
{
    slider->setBounds(0, 0, getWidth(), getWidth());
    int sinkY = slider->getY() + slider->getHeight() + 3;
    sinkY = slider->getTextBoxPosition() == Slider::NoTextBox ? sinkY - 8 : sinkY;
    modulationSink->setTopLeftPosition(slider->getX() + slider->getWidth() / 2.0 - modulationSink->getWidth() / 2.0,
                                       sinkY);
}

void ModulatedComponent::setTextBoxStyle(const Slider::TextEntryBoxPosition newPosition, const bool isReadOnly,
                      const int textEntryBoxWidth, const int textEntryBoxHeight)
{
    slider->setTextBoxStyle(newPosition, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    resized();
}
