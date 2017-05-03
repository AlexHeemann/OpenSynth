/*
  ==============================================================================

    AmpComponent.cpp
    Created: 6 Oct 2016 3:15:30pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AmpComponent.h"
#include "EnvelopeParameterContainer.h"

//==============================================================================
AmpComponent::AmpComponent(OpenSynthAudioProcessor &processor) : processor(processor),
                                                                  attackLabel(String::empty, "A"),
                                                                  decayLabel(String::empty, "D"),
                                                                  sustainLabel(String::empty, "S"),
                                                                  releaseLabel(String::empty, "R"),
                                                                  ampLabel(String::empty, "Gain")
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(140, 105);
    
    addAndMakeVisible(gainKnob = new ParameterSlider(*processor.level));
    gainKnob->setSliderStyle(Slider::Rotary);
    gainKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 15);
    gainKnob->setColour(Slider::textBoxBackgroundColourId, Colours::midnightblue);
    ampLabel.attachToComponent(gainKnob, false);
    ampLabel.setColour (Label::textColourId, Colours::black);
    ampLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    
    EnvelopeParameterContainer& ampEnvelopeParameterContainer = processor.getAmpEnvelopeParameterContainer();
    addAndMakeVisible(attackSlider = new ParameterSlider(*ampEnvelopeParameterContainer.getAttackRateParameter()));
    attackSlider->setSliderStyle(Slider::LinearVertical);
    attackLabel.attachToComponent(attackSlider, false);
    attackLabel.setColour (Label::textColourId, Colours::black);
    attackLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    
    addAndMakeVisible(decaySlider = new ParameterSlider(*ampEnvelopeParameterContainer.getDecayRateParameter()));
    decaySlider->setSliderStyle(Slider::LinearVertical);
    decayLabel.attachToComponent(decaySlider, false);
    decayLabel.setColour (Label::textColourId, Colours::black);
    decayLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    
    addAndMakeVisible(sustainSlider = new ParameterSlider(*ampEnvelopeParameterContainer.getSustainLevelParameter()));
    sustainSlider->setSliderStyle(Slider::LinearVertical);
    sustainLabel.attachToComponent(sustainSlider, false);
    sustainLabel.setColour (Label::textColourId, Colours::black);
    sustainLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    
    addAndMakeVisible(releaseSlider = new ParameterSlider(*ampEnvelopeParameterContainer.getReleaseRateParameter()));
    releaseSlider->setSliderStyle(Slider::LinearVertical);
    releaseLabel.attachToComponent(releaseSlider, false);
    releaseLabel.setColour (Label::textColourId, Colours::black);
    releaseLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
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
    attackSlider->setBounds(5, 22, 20, 80);
    decaySlider->setBounds(28, 22, 20, 80);
    sustainSlider->setBounds(51, 22, 20, 80);
    releaseSlider->setBounds(69, 22, 20, 80);
}

void AmpComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
