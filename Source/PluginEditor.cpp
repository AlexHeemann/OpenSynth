/*
  ==============================================================================

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterSlider.h"
#include "FilterComponent.h"
#include "LFOComponent.h"
#include "OscillatorComponent.h"
#include "OscillatorParameterContainer.h"
#include "LFOParameterContainer.h"

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
    addAndMakeVisible(ampComponent = new AmpComponent(*static_cast<AmpParameterContainer*>(processor.getParameterContainer(0))));
    
    OscillatorParameterContainer* oscParameterContainer = static_cast<OscillatorParameterContainer*>(processor.getParameterContainer(1));
    addAndMakeVisible(oscillatorComponent = new OscillatorComponent(*this,
                                                                    oscParameterContainer,
                                                                    processor.getModulationMatrix()));
    OscillatorParameterContainer* osc2ParameterContainer = static_cast<OscillatorParameterContainer*>(processor.getParameterContainer(4));
    addAndMakeVisible(oscillator2Component = new OscillatorComponent(*this,
                                                                    osc2ParameterContainer,
                                                                    processor.getModulationMatrix()));
    
//    addAndMakeVisible(filterComponent = new FilterComponent(*this));
    
//    addAndMakeVisible(delayComponent = new DelayComponent(owner.getDelayParameterContainer()));
//    addAndMakeVisible(reverbComponent = new ReverbComponent(owner.getReverbParameterContainer()));
    LFOParameterContainer* lfoParameterContainer = static_cast<LFOParameterContainer*>(processor.getParameterContainer(3));
    addAndMakeVisible(lfoComponent = new LFOComponent(*this,
                                                      lfoParameterContainer,
                                                      processor.getModulationMatrix()));
    addAndMakeVisible(envelope1Component = new EnvelopeComponent(*static_cast<EnvelopeParameterContainer*>(processor.getParameterContainer(2))));
//    addAndMakeVisible(envelope2Component = new EnvelopeComponent(owner.getEnvelope2ParameterContainer()));

	// add the midi keyboard component..
	addAndMakeVisible(keyboardComponent);

	// add the triangular resizer component for the bottom-right of the UI
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(200, 150, 800, 300);

	// set our component's size
	setSize(700, 550);
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
    oscillator2Component->setTopLeftPosition(oscillatorComponent->getX(), oscillatorComponent->getY() + oscillatorComponent->getHeight() + 10);
//    filterComponent->setTopLeftPosition(oscillatorComponent->getX() + oscillatorComponent->getWidth() + 10, oscillatorComponent->getY());
//    delayComponent->setTopRightPosition(filterComponent->getX() + filterComponent->getWidth(), filterComponent->getY() + filterComponent->getHeight() + 10);
    ampComponent->setTopLeftPosition(oscillatorComponent->getX() + oscillatorComponent->getWidth() + 10, oscillatorComponent->getY());
//    reverbComponent->setTopLeftPosition(ampComponent->getX(), ampComponent->getY() + ampComponent->getHeight() + 10);
    lfoComponent->setTopLeftPosition(oscillator2Component->getX(), oscillator2Component->getY() + oscillator2Component->getHeight() + 10);
    envelope1Component->setTopLeftPosition(ampComponent->getX() + ampComponent->getWidth() + 10, ampComponent->getY());
//    envelope2Component->setTopLeftPosition(envelope1Component->getX() + envelope1Component->getWidth() + 10, envelope1Component->getY());
}

//==============================================================================

int OpenSynthAudioProcessorEditor::dragOperationStarted()
{
    return 1;
}

int OpenSynthAudioProcessorEditor::dragOperationEnded()
{
    return 1;
}

//==============================================================================


