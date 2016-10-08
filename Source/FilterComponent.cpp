/*
  ==============================================================================

    FilterComponent.cpp
    Created: 8 Oct 2016 4:47:11pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(NoisemakerAudioProcessor &processor) : processor(processor),
attackLabel(String::empty, "A"),
decayLabel(String::empty, "D"),
sustainLabel(String::empty, "S"),
releaseLabel(String::empty, "R"),
frequencyLabel(String::empty, "Frequency")
{
    setSize(140, 105);
    
    addAndMakeVisible(frequencyKnob = new ParameterSlider(*processor.filterFrequency));
    frequencyKnob->setSliderStyle(Slider::Rotary);
    frequencyKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 15);
    frequencyLabel.attachToComponent(frequencyKnob, false);
    
    addAndMakeVisible(attackSlider = new ParameterSlider(*processor.attackRateAmp));
    attackSlider->setSliderStyle(Slider::LinearVertical);
    attackLabel.attachToComponent(attackSlider, false);
    
    addAndMakeVisible(decaySlider = new ParameterSlider(*processor.decayRateAmp));
    decaySlider->setSliderStyle(Slider::LinearVertical);
    decayLabel.attachToComponent(decaySlider, false);
    
    addAndMakeVisible(sustainSlider = new ParameterSlider(*processor.sustainLevelAmp));
    sustainSlider->setSliderStyle(Slider::LinearVertical);
    sustainLabel.attachToComponent(sustainSlider, false);
    
    addAndMakeVisible(releaseSlider = new ParameterSlider(*processor.releaseRateAmp));
    releaseSlider->setSliderStyle(Slider::LinearVertical);
    releaseLabel.attachToComponent(releaseSlider, false);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (Graphics& g)
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
    
    frequencyKnob->setBounds(90, 22, 47, 70);
    attackSlider->setBounds(5, 22, 20, 80);
    decaySlider->setBounds(28, 22, 20, 80);
    sustainSlider->setBounds(51, 22, 20, 80);
    releaseSlider->setBounds(69, 22, 20, 80);
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
