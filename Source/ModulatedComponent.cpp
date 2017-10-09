/*
  ==============================================================================

    ModulatedComponent.cpp
    Created: 10 May 2017 1:26:18pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ModulatedComponent.h"
#include "ModulationOverview.h"

//==============================================================================
ModulatedComponent::ModulatedComponent(OpenSynthAudioProcessorEditor& editor, AudioProcessorParameter& p, int ID) : ID(ID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(slider = new ParameterSlider(p));
    addAndMakeVisible(modulationSink = new ModulationSink(editor, ID));
}

ModulatedComponent::~ModulatedComponent()
{
}

void ModulatedComponent::paint (Graphics& g)
{
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void ModulatedComponent::update()
{
    modulationSink->update();
}

void ModulatedComponent::resized()
{
    slider->setBounds(0, 0, getWidth(), getHeight() - modulationSink->getHeight());
    int sinkYOffset = slider->getSliderStyle() == Slider::Rotary ? 3 : 10;
    int sinkY = slider->getY() + slider->getHeight() + sinkYOffset;
    sinkY = slider->getTextBoxPosition() == Slider::NoTextBox ? sinkY - 8 : sinkY;
    int sinkX = slider->getX() + slider->getWidth() / 2.0 - modulationSink->getWidth() / 2.0;
    if (slider->getSliderStyle() == Slider::LinearHorizontal && slider->getTextBoxPosition() == Slider::TextBoxBelow)
    {
        sinkY = sinkY - slider->getTextBoxHeight() - modulationSink->getHeight() / 2.0;
        sinkX = sinkX - slider->getTextBoxWidth() / 2.0 - modulationSink->getWidth() / 2.0 - 5;
    }
    modulationSink->setTopLeftPosition(sinkX,
                                       sinkY);
}

void ModulatedComponent::setTextBoxStyle(const Slider::TextEntryBoxPosition newPosition, const bool isReadOnly,
                      const int textEntryBoxWidth, const int textEntryBoxHeight)
{
    slider->setTextBoxStyle(newPosition, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    resized();
}
