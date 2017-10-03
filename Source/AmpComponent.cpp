/*
  ==============================================================================

    AmpComponent.cpp
    Created: 6 Oct 2016 3:15:30pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AmpComponent.h"

//==============================================================================
AmpComponent::AmpComponent(AmpParameterContainer &parameterContainer) : parameterContainer(parameterContainer),
                                                                  gainLabel(String::empty, "Gain")
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(140, 105);
    
    addAndMakeVisible(gainKnob = new ParameterSlider(*parameterContainer.getGainParameter()));
    gainKnob->setSliderStyle(Slider::Rotary);
    gainKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 15);
    gainKnob->setColour(Slider::textBoxBackgroundColourId, Colours::midnightblue);
    gainLabel.attachToComponent(gainKnob, false);
    gainLabel.setColour (Label::textColourId, Colours::black);
    gainLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
}

AmpComponent::~AmpComponent()
{
}

void AmpComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    
    gainKnob->setBounds(90, 22, 47, 70);
}

void AmpComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
