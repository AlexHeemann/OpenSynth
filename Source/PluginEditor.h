/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class NoisemakerAudioProcessorEditor  : public AudioProcessorEditor, private Timer, private ComboBox::Listener
{
public:
    NoisemakerAudioProcessorEditor (NoisemakerAudioProcessor&);
    ~NoisemakerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	class ParameterSlider;

    NoisemakerAudioProcessor& processor;
	MidiKeyboardComponent keyboardComponent;

	Label timecodeDisplayLabel, gainLabel, delayLabel, filterLabel;
	ScopedPointer<ParameterSlider> gainSlider, delaySlider, filterSlider;
	ScopedPointer<ResizableCornerComponent> resizer;
	ScopedPointer<ComboBox> waveformBox;
	ComponentBoundsConstrainer resizeLimits;

	AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

	//==============================================================================
	NoisemakerAudioProcessor& getProcessor() const
	{
		return static_cast<NoisemakerAudioProcessor&> (processor);
	}

	void updateTimecodeDisplay(AudioPlayHead::CurrentPositionInfo);

	virtual void comboBoxChanged(ComboBox* comboBoxThatHasChanged);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoisemakerAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
