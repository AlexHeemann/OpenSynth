/*
  ==============================================================================

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterSlider.h"

//==============================================================================
OpenSynthAudioProcessorEditor::OpenSynthAudioProcessorEditor (OpenSynthAudioProcessor& owner)
    : AudioProcessorEditor (&owner), processor (owner),
	keyboardComponent(owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
	gainLabel(String::empty, "Gain:"),
	delayLabel(String::empty, "Delay:"),
	filterLabel(String::empty, "Filter:"),
	envAttackLabel(String::empty, "Attack:"),
	envDecayLabel(String::empty, "Decay:")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(ampComponent = new AmpComponent(owner));
    addAndMakeVisible(filterComponent = new FilterComponent(owner));
    addAndMakeVisible(oscillatorComponent = new OscillatorComponent(owner));
    addAndMakeVisible(delayComponent = new DelayComponent(owner));
    addAndMakeVisible(reverbComponent = new ReverbComponent(owner.getReverbParameterContainer()));

	// add the midi keyboard component..
	addAndMakeVisible(keyboardComponent);

	// add the triangular resizer component for the bottom-right of the UI
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(200, 150, 800, 300);

	// set our component's size
	setSize(550, 410);
}

OpenSynthAudioProcessorEditor::~OpenSynthAudioProcessorEditor()
{
}

//==============================================================================
void OpenSynthAudioProcessorEditor::paint(Graphics& g)
{
	g.setGradientFill(ColourGradient(Colours::white, 0, 0,
		Colours::lightgrey, 0, (float)getHeight(), false));
	g.fillAll();
}

void OpenSynthAudioProcessorEditor::resized()
{
	Rectangle<int> r(getLocalBounds().reduced(8));
	keyboardComponent.setBounds(r.removeFromBottom(70));
    
    oscillatorComponent->setTopLeftPosition(r.getX(), r.getY());
    filterComponent->setTopLeftPosition(oscillatorComponent->getX() + oscillatorComponent->getWidth() + 10, oscillatorComponent->getY());
    delayComponent->setTopRightPosition(filterComponent->getX() + filterComponent->getWidth(), filterComponent->getY() + filterComponent->getHeight() + 10);
    ampComponent->setTopLeftPosition(filterComponent->getX() + filterComponent->getWidth() + 10, filterComponent->getY());
    reverbComponent->setTopLeftPosition(ampComponent->getX(), ampComponent->getY() + ampComponent->getHeight() + 10);
}

//==============================================================================

void OpenSynthAudioProcessorEditor::dragOperationStarted()
{
}

void OpenSynthAudioProcessorEditor::dragOperationEnded()
{
}

//==============================================================================


