/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterSlider.h"

//==============================================================================
NoisemakerAudioProcessorEditor::NoisemakerAudioProcessorEditor (NoisemakerAudioProcessor& owner)
    : AudioProcessorEditor (&owner), processor (owner),
	keyboardComponent(owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
	timecodeDisplayLabel(String::empty),
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

	// add the midi keyboard component..
	addAndMakeVisible(keyboardComponent);

	// add the triangular resizer component for the bottom-right of the UI
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(200, 150, 800, 300);

	// set our component's initial size to be the last one that was stored in the filter's settings
	setSize(600, 400);

	// start a timer which will keep our timecode display updated
	startTimerHz(30);
}

NoisemakerAudioProcessorEditor::~NoisemakerAudioProcessorEditor()
{
}

//==============================================================================
void NoisemakerAudioProcessorEditor::paint(Graphics& g)
{
	g.setGradientFill(ColourGradient(Colours::white, 0, 0,
		Colours::lightgrey, 0, (float)getHeight(), false));
	g.fillAll();
}

void NoisemakerAudioProcessorEditor::resized()
{
	Rectangle<int> r(getLocalBounds().reduced(8));
	keyboardComponent.setBounds(r.removeFromBottom(70));
    
    ampComponent->setTopLeftPosition(r.getWidth() - ampComponent->getWidth(), r.getY());
    filterComponent->setTopLeftPosition(r.getWidth() - ampComponent->getWidth() - filterComponent->getWidth() - 10, r.getY());
    oscillatorComponent->setTopLeftPosition(r.getX(), r.getY());
}

//==============================================================================
void NoisemakerAudioProcessorEditor::timerCallback()
{
	updateTimecodeDisplay(getProcessor().lastPosInfo);
}

void NoisemakerAudioProcessorEditor::dragOperationStarted()
{
}

void NoisemakerAudioProcessorEditor::dragOperationEnded()
{
}

//==============================================================================
// quick-and-dirty function to format a timecode string
static String timeToTimecodeString(double seconds)
{
	const int millisecs = roundToInt(std::abs(seconds * 1000.0));

	return String::formatted("%s%02d:%02d:%02d.%03d",
		seconds < 0 ? "-" : "",
		millisecs / 360000,
		(millisecs / 60000) % 60,
		(millisecs / 1000) % 60,
		millisecs % 1000);
}

// quick-and-dirty function to format a bars/beats string
static String quarterNotePositionToBarsBeatsString(double quarterNotes, int numerator, int denominator)
{
	if (numerator == 0 || denominator == 0)
		return "1|1|000";

	const int quarterNotesPerBar = (numerator * 4 / denominator);
	const double beats = (fmod(quarterNotes, quarterNotesPerBar) / quarterNotesPerBar) * numerator;

	const int bar = ((int)quarterNotes) / quarterNotesPerBar + 1;
	const int beat = ((int)beats) + 1;
	const int ticks = ((int)(fmod(beats, 1.0) * 960.0 + 0.5));

	return String::formatted("%d|%d|%03d", bar, beat, ticks);
}

// Updates the text in our position label.
void NoisemakerAudioProcessorEditor::updateTimecodeDisplay(AudioPlayHead::CurrentPositionInfo pos)
{
	if (lastDisplayedPosition != pos)
	{
		lastDisplayedPosition = pos;

		MemoryOutputStream displayText;

		displayText << "[" << SystemStats::getJUCEVersion() << "]   "
			<< String(pos.bpm, 2) << " bpm, "
			<< pos.timeSigNumerator << '/' << pos.timeSigDenominator
			<< "  -  " << timeToTimecodeString(pos.timeInSeconds)
			<< "  -  " << quarterNotePositionToBarsBeatsString(pos.ppqPosition,
				pos.timeSigNumerator,
				pos.timeSigDenominator);

		if (pos.isRecording)
			displayText << "  (recording)";
		else if (pos.isPlaying)
			displayText << "  (playing)";

		timecodeDisplayLabel.setText(displayText.toString(), dontSendNotification);
	}
}

//==============================================================================


