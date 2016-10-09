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
frequencyLabel(String::empty, "Frequency"),
envAmountLabel(String::empty, "Env Amount")
{
    setSize(160, 170);
    
    addAndMakeVisible(frequencyKnob = new ParameterSlider(*processor.filterFrequency));
    frequencyKnob->setSliderStyle(Slider::Rotary);
    frequencyKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 68, 15);
    frequencyLabel.attachToComponent(frequencyKnob, false);
    
    addAndMakeVisible(envelopeAmountKnob = new ParameterSlider(*processor.envelopeAmountFilter));
    envelopeAmountKnob->setSliderStyle(Slider::Rotary);
    envelopeAmountKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    envAmountLabel.attachToComponent(envelopeAmountKnob, false);
    
    addAndMakeVisible(attackSlider = new ParameterSlider(*processor.attackRateFilter));
    attackSlider->setSliderStyle(Slider::LinearVertical);
    attackLabel.attachToComponent(attackSlider, false);
    
    addAndMakeVisible(decaySlider = new ParameterSlider(*processor.decayRateFilter));
    decaySlider->setSliderStyle(Slider::LinearVertical);
    decayLabel.attachToComponent(decaySlider, false);
    
    addAndMakeVisible(sustainSlider = new ParameterSlider(*processor.sustainLevelFilter));
    sustainSlider->setSliderStyle(Slider::LinearVertical);
    sustainLabel.attachToComponent(sustainSlider, false);
    
    addAndMakeVisible(releaseSlider = new ParameterSlider(*processor.releaseRateFilter));
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
    
    frequencyKnob->setBounds(90, 22, 60, 70);
    envelopeAmountKnob->setBounds(5, 125, 80, 45);
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
