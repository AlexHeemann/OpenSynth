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
#include "OscillatorComponent.h"
#include "DelayComponent.h"
#include "ReverbComponent.h"
#include "EnvelopeComponent.h"

class LFOComponent;
class ParameterSlider;
class FilterComponent;

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

	virtual int dragOperationStarted();
	virtual int dragOperationEnded();
    
    OpenSynthAudioProcessor& getProcessor() const
    {
        return static_cast<OpenSynthAudioProcessor&> (processor);
    }

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
    ScopedPointer<LFOComponent> lfoComponent;
    ScopedPointer<EnvelopeComponent> envelope1Component;
    ScopedPointer<EnvelopeComponent> envelope2Component;
	ComponentBoundsConstrainer resizeLimits;

	//==============================================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenSynthAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
