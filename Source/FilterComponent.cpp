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
FilterComponent::FilterComponent(OpenSynthAudioProcessorEditor &editor) : editor(editor), processor(editor.getProcessor()),
frequencyLabel(new Label(String::empty, "Frequency")),
resonanceLabel(new Label(String::empty, "Resonance"))
{
//    FilterParameterContainer& filterParameterContainer = processor.getFilterParameterContainer();
//    addAndMakeVisible(frequencyKnob = new ModulatedComponent(editor, *filterParameterContainer.getFilterFrequencyParameter(), ParameterIDFilterCutoff));
    frequencyKnob->getSlider()->setSliderStyle(Slider::Rotary);
    frequencyKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 15);
    frequencyKnob->getSlider()->setColour(Slider::textBoxBackgroundColourId, Colours::midnightblue);
    frequencyLabel->setColour (Label::backgroundColourId, Colours::transparentWhite);
    frequencyLabel->setColour (Label::textColourId, Colours::black);
    frequencyKnob->setListener(this);
    addAndMakeVisible(frequencyLabel);
    
//    addAndMakeVisible(resonanceKnob = new ModulatedComponent(editor, *filterParameterContainer.getFilterResonanceParameter(), ParameterIDFilterResonance));
    resonanceKnob->getSlider()->setSliderStyle(Slider::Rotary);
    resonanceKnob->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    resonanceLabel->setColour (Label::textColourId, Colours::black);
    resonanceLabel->setColour (Label::backgroundColourId, Colours::transparentWhite);
    addAndMakeVisible(resonanceLabel);
    resonanceKnob->getSlider()->setListener(this);
    
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
    
    frequencyModulationPopover = new ModulationPopover();
    frequencyModulationPopover->addListener(this);
    
    setSize(150, 180);
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
        Component* parent = getParentComponent();
        if (parent != nullptr)
        {
            parent->addAndMakeVisible(frequencyModulationPopover);
            resized();
        }
        frequencyModulationPopover->setSourceID(sourceID);
        frequencyKnob->update();
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
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    filterTypeComboBox->setBounds(5, 22, 140, 25);
    frequencyLabel->setBounds(filterTypeComboBox->getX(), filterTypeComboBox->getY() + filterTypeComboBox->getHeight() + 10, 65, 20);
    frequencyKnob->setBounds(frequencyLabel->getX(), frequencyLabel->getY() + frequencyLabel->getHeight() + 5, 65, 90);
    frequencyModulationPopover->setTopLeftPosition(getX() + frequencyKnob->getX() - frequencyModulationPopover->getWidth() - 10,
                                                   getY() + frequencyKnob->getY());
    resonanceLabel->setBounds(frequencyLabel->getX() + frequencyLabel->getWidth() + 5, frequencyLabel->getY(), 65, 20);
    resonanceKnob->setBounds(resonanceLabel->getX() + resonanceLabel->getWidth() / 2.0 - 20, frequencyKnob->getY(), 50, 75);
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
