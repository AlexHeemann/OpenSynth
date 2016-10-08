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
AmpComponent::AmpComponent(NoisemakerAudioProcessor &processor) : processor(processor)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(121, 111);
    
    addAndMakeVisible(gainKnob = new ParameterSlider(*processor.level));
    gainKnob->setSliderStyle(Slider::Rotary);
    
    addAndMakeVisible(attackSlider = new ParameterSlider(*processor.attackRate));
    attackSlider->setSliderStyle(Slider::LinearVertical);
    addAndMakeVisible(decaySlider = new ParameterSlider(*processor.decayRate));
    decaySlider->setSliderStyle(Slider::LinearVertical);
    addAndMakeVisible(sustainSlider = new ParameterSlider(*processor.sustainLevel));
    sustainSlider->setSliderStyle(Slider::LinearVertical);
    addAndMakeVisible(releaseSlider = new ParameterSlider(*processor.releaseRate));
    releaseSlider->setSliderStyle(Slider::LinearVertical);
}

AmpComponent::~AmpComponent()
{
}

void AmpComponent::paint (Graphics& g)
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
    g.drawText ("AmpComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
    
    gainKnob->setBounds(85, 10, 35, 35);
    attackSlider->setBounds(10, 10, 20, 80);
    decaySlider->setBounds(32, 10, 20, 80);
    sustainSlider->setBounds(57, 10, 20, 80);
    releaseSlider->setBounds(82, 10, 20, 80);
}

void AmpComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
