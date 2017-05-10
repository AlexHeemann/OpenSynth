/*
  ==============================================================================

    FilterComponent.cpp
    Created: 8 Oct 2016 4:47:11pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterComponent.h"
#include "FilterProcessor.h"
#include "EnvelopeParameterContainer.h"
#include "FilterParameterContainer.h"
#include "DragAndDropListener.h"

//==============================================================================
FilterComponent::FilterComponent(OpenSynthAudioProcessor &processor) : processor(processor),
attackLabel(String::empty, "A"),
decayLabel(String::empty, "D"),
sustainLabel(String::empty, "S"),
releaseLabel(String::empty, "R"),
frequencyLabel(String::empty, "Frequency"),
envAmountLabel(String::empty, "Env Amount"),
resonanceLabel(String::empty, "Resonance")
{
    setSize(160, 220);
    
    FilterParameterContainer& filterParameterContainer = processor.getFilterParameterContainer();
    addAndMakeVisible(frequencyKnob = new ModulatedComponent(*filterParameterContainer.getFilterFrequencyParameter(), ParameterIDFilterCutoff));
    frequencyKnob->getSlider()->setSliderStyle(Slider::Rotary);
    frequencyKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 15);
    frequencyKnob->getSlider()->setColour(Slider::textBoxBackgroundColourId, Colours::midnightblue);
    frequencyLabel.attachToComponent(frequencyKnob, false);
    frequencyLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    frequencyLabel.setColour (Label::textColourId, Colours::black);
    frequencyKnob->getSlider()->setListener(this);
    
    addAndMakeVisible(envelopeAmountKnob = new ParameterSlider(*filterParameterContainer.getEnvelopeAmountParameter(), ParameterIDFilterCutoff));
    envelopeAmountKnob->setSliderStyle(Slider::Rotary);
    envelopeAmountKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    envAmountLabel.attachToComponent(envelopeAmountKnob, false);
    envAmountLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    envAmountLabel.setColour (Label::textColourId, Colours::black);
    envelopeAmountKnob->setListener(this);
    
    addAndMakeVisible(resonanceKnob = new ModulatedComponent(*filterParameterContainer.getFilterResonanceParameter(), ParameterIDFilterResonance));
    resonanceKnob->getSlider()->setSliderStyle(Slider::Rotary);
    resonanceKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    resonanceLabel.attachToComponent(resonanceKnob, false);
    resonanceLabel.setColour (Label::textColourId, Colours::black);
    resonanceLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    resonanceKnob->getSlider()->setListener(this);
    
    EnvelopeParameterContainer& filterEnvelopeParameterContainer = processor.getFilterEnvelopeParameterContainer();
    addAndMakeVisible(attackSlider = new ParameterSlider(*filterEnvelopeParameterContainer.getAttackRateParameter(), ParameterIDEnvelope2Attack));
    attackSlider->setSliderStyle(Slider::LinearVertical);
    attackLabel.attachToComponent(attackSlider, false);
    attackLabel.setColour (Label::textColourId, Colours::black);
    attackLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    attackSlider->setListener(this);
    
    addAndMakeVisible(decaySlider = new ParameterSlider(*filterEnvelopeParameterContainer.getDecayRateParameter(), ParameterIDEnvelope2Decay));
    decaySlider->setSliderStyle(Slider::LinearVertical);
    decayLabel.attachToComponent(decaySlider, false);
    decayLabel.setColour (Label::textColourId, Colours::black);
    decayLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    decaySlider->setListener(this);
    
    addAndMakeVisible(sustainSlider = new ParameterSlider(*filterEnvelopeParameterContainer.getSustainLevelParameter(), ParameterIDEnvelope2Sustain));
    sustainSlider->setSliderStyle(Slider::LinearVertical);
    sustainLabel.attachToComponent(sustainSlider, false);
    sustainLabel.setColour (Label::textColourId, Colours::black);
    sustainLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    sustainSlider->setListener(this);
    
    addAndMakeVisible(releaseSlider = new ParameterSlider(*filterEnvelopeParameterContainer.getReleaseRateParameter(), ParameterIDEnvelope2Release));
    releaseSlider->setSliderStyle(Slider::LinearVertical);
    releaseLabel.attachToComponent(releaseSlider, false);
    releaseLabel.setColour (Label::textColourId, Colours::black);
    releaseLabel.setColour (Label::backgroundColourId, Colours::transparentWhite);
    releaseSlider->setListener(this);
    
    addAndMakeVisible (filterTypeComboBox = new ComboBox ("Osc 1 Combo Box"));
    filterTypeComboBox->setEditableText (false);
    filterTypeComboBox->setJustificationType (Justification::centredLeft);
    filterTypeComboBox->setTextWhenNothingSelected (TRANS("Filter Type"));
    filterTypeComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    filterTypeComboBox->addItem ("Low Pass", FilterProcessor::LowPass);
    filterTypeComboBox->addItem ("High Pass", FilterProcessor::HighPass);
    filterTypeComboBox->addItem ("Band Pass", FilterProcessor::BandPass);
    filterTypeComboBox->addItem ("All Pass", FilterProcessor::AllPass);
    filterTypeComboBox->addListener (this);
    filterTypeComboBox->setSelectedId(FilterProcessor::LowPass);
    
    addChildComponent(frequencyModulationPopover = new ModulationPopover());
    frequencyModulationPopover->addListener(this);
}

FilterComponent::~FilterComponent()
{
    frequencyModulationPopover->removeListener(this);
}

void FilterComponent::modulationPopoverValueChanged(ModulationPopover* modulationPopover)
{
    if (modulationPopover == frequencyModulationPopover)
    {
        processor.updateModulationAmount(modulationPopover->getSourceID(), ParameterIDFilterCutoff, modulationPopover->getModulationAmount());
    }
}

void FilterComponent::itemDropped(const int sourceID, const int destinationID)
{
    processor.connect(sourceID, destinationID);
    if (destinationID == ParameterIDFilterCutoff)
    {
        frequencyModulationPopover->setSourceID(sourceID);
        frequencyModulationPopover->setVisible(true);
    }
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
    
    frequencyKnob->setBounds(90, 22, 65, 90);
    frequencyModulationPopover->setTopLeftPosition(frequencyKnob->getX() - frequencyModulationPopover->getWidth(), frequencyKnob->getY());
    envelopeAmountKnob->setBounds(5, 125, 80, 45);
    resonanceKnob->setBounds(80, 135, 40, 45);
    attackSlider->setBounds(5, 22, 20, 80);
    decaySlider->setBounds(28, 22, 20, 80);
    sustainSlider->setBounds(51, 22, 20, 80);
    releaseSlider->setBounds(69, 22, 20, 80);
    filterTypeComboBox->setBounds(5, 180, 140, 25);
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FilterComponent::mouseDown(const MouseEvent& event)
{
    frequencyModulationPopover->setVisible(false);
}

void FilterComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == filterTypeComboBox)
    {
        switch (comboBoxThatHasChanged->getSelectedId())
        {
            case FilterProcessor::LowPass:
                processor.setFilterType(FilterProcessor::LowPass);
                break;
            case FilterProcessor::HighPass:
                processor.setFilterType(FilterProcessor::HighPass);
                break;
            case FilterProcessor::BandPass:
                processor.setFilterType(FilterProcessor::BandPass);
                break;
            case FilterProcessor::AllPass:
                processor.setFilterType(FilterProcessor::AllPass);
                break;
        }
    }
}
