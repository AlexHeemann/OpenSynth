/*
  ==============================================================================

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ModulationConnector.h"
#include "AmpComponent.h"
#include "FilterComponent.h"
#include "OscillatorComponent.h"
#include "DelayComponent.h"
#include "ReverbComponent.h"

class ParameterSlider;

//==============================================================================
/**
*/
class OpenSynthAudioProcessorEditor  : public AudioProcessorEditor, public DragAndDropContainer
{
public:
    OpenSynthAudioProcessorEditor (OpenSynthAudioProcessor&);
    ~OpenSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	virtual void dragOperationStarted();
	virtual void dragOperationEnded();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    OpenSynthAudioProcessor& processor;
	MidiKeyboardComponent keyboardComponent;

	Label gainLabel, delayLabel, filterLabel, envAttackLabel, envDecayLabel;
	ScopedPointer<ParameterSlider> gainSlider, delaySlider, filterSlider, envAttackSlider, envDecaySlider;
	ScopedPointer<ResizableCornerComponent> resizer;
	ScopedPointer<ComboBox> waveformBox;
	ScopedPointer<ModulationConnector> envelopeConnector;
    ScopedPointer<AmpComponent> ampComponent;
    ScopedPointer<FilterComponent> filterComponent;
    ScopedPointer<OscillatorComponent> oscillatorComponent;
    ScopedPointer<DelayComponent> delayComponent;
    ScopedPointer<ReverbComponent> reverbComponent;
	ComponentBoundsConstrainer resizeLimits;

	//==============================================================================
	OpenSynthAudioProcessor& getProcessor() const
	{
		return static_cast<OpenSynthAudioProcessor&> (processor);
	}
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenSynthAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
