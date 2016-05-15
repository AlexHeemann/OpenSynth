/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// (may move this class into the library itself at some point in the future..)
class NoisemakerAudioProcessorEditor::ParameterSlider : public Slider,
	private Timer
{
public:
	ParameterSlider(AudioProcessorParameter& p)
		: Slider(p.getName(256)), param(p)
	{
		setRange(0.0, 1.0, 0.0);
		startTimerHz(30);
		updateSliderPos();
	}

	void valueChanged() override
	{
		param.setValueNotifyingHost((float)Slider::getValue());
	}

	void timerCallback() override { updateSliderPos(); }

	void startedDragging() override { param.beginChangeGesture(); }
	void stoppedDragging() override { param.endChangeGesture(); }

	double getValueFromText(const String& text) override { return param.getValueForText(text); }
	String getTextFromValue(double value) override { return param.getText((float)value, 1024); }

	void updateSliderPos()
	{
		const float newValue = param.getValue();

		if (newValue != (float)Slider::getValue() && !isMouseButtonDown())
			Slider::setValue(newValue);
	}

	AudioProcessorParameter& param;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider)
};

//==============================================================================
NoisemakerAudioProcessorEditor::NoisemakerAudioProcessorEditor (NoisemakerAudioProcessor& owner)
    : AudioProcessorEditor (&owner), processor (owner),
	keyboardComponent(owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
	timecodeDisplayLabel(String::empty),
	gainLabel(String::empty, "Gain:"),
	delayLabel(String::empty, "Delay:"),
	filterLabel(String::empty, "Filter:")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	// add some sliders..
	addAndMakeVisible(gainSlider = new ParameterSlider(*owner.gainParam));
	gainSlider->setSliderStyle(Slider::Rotary);

	addAndMakeVisible(delaySlider = new ParameterSlider(*owner.delayParam));
	delaySlider->setSliderStyle(Slider::Rotary);

	addAndMakeVisible(filterSlider = new ParameterSlider(*owner.filterFrequencyParam));
	filterSlider->setSliderStyle(Slider::Rotary);

	// add some labels for the sliders..
	gainLabel.attachToComponent(gainSlider, false);
	gainLabel.setFont(Font(11.0f));

	delayLabel.attachToComponent(delaySlider, false);
	delayLabel.setFont(Font(11.0f));

	filterLabel.attachToComponent(filterSlider, false);
	filterLabel.setFont(Font(11.0f));

	// add the midi keyboard component..
	addAndMakeVisible(keyboardComponent);

	waveformBox = new ComboBox("Waveform");
	waveformBox->setText("Waveform");
	waveformBox->addItem("Sine", 1);
	waveformBox->addItem("Square", 2);
	waveformBox->addItem("Sawtooth", 3);
    waveformBox->addItem("Triangle", 4);

	waveformBox->addListener(this);
	addAndMakeVisible(waveformBox);


	// add the triangular resizer component for the bottom-right of the UI
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(200, 150, 800, 300);

	// set our component's initial size to be the last one that was stored in the filter's settings
	setSize(owner.lastUIWidth,
		owner.lastUIHeight);

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
	// This lays out our child components...

	Rectangle<int> r(getLocalBounds().reduced(8));

	waveformBox->setBounds(r.removeFromTop(26));
	keyboardComponent.setBounds(r.removeFromBottom(70));

	r.removeFromTop(30);
	Rectangle<int> sliderArea(r.removeFromTop(50));
	gainSlider->setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth() / 2)));
	delaySlider->setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth())));
	filterSlider->setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth())));

	resizer->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);

	getProcessor().lastUIWidth = getWidth();
	getProcessor().lastUIHeight = getHeight();
}

//==============================================================================
void NoisemakerAudioProcessorEditor::timerCallback()
{
	updateTimecodeDisplay(getProcessor().lastPosInfo);
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
// Combobox Listener
void NoisemakerAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
	processor.setWaveform((Waveform)(comboBoxThatHasChanged->getSelectedId() - 1));
}

