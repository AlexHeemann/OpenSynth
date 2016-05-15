/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

typedef enum 
{
	WaveformSine,
	WaveformSquare,
	WaveformSawtooth,
    WaveformTriangle,
} Waveform;


//==============================================================================
/**
*/
class NoisemakerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NoisemakerAudioProcessor();
    ~NoisemakerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
	void reset() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

	//==============================================================================
	void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override
	{
		jassert(!isUsingDoublePrecision());
		process(buffer, midiMessages, delayBufferFloat);
	}

	void processBlock(AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override
	{
		jassert(isUsingDoublePrecision());
		process(buffer, midiMessages, delayBufferDouble);
	}

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void setWaveform(Waveform waveform);

	// this is kept up to date with the midi messages that arrive, and the UI component
	// registers with it so it can represent the incoming messages
	MidiKeyboardState keyboardState;

	// this keeps a copy of the last set of time info that was acquired during an audio
	// callback - the UI component will read this and display it.
	AudioPlayHead::CurrentPositionInfo lastPosInfo;

	// these are used to persist the UI's size - the values are stored along with the
	// filter's other parameters, and the UI component will update them when it gets
	// resized.
	int lastUIWidth, lastUIHeight;

	// Our parameters
	AudioParameterFloat* gainParam;
	AudioParameterFloat* delayParam;
	AudioParameterFloat* filterFrequencyParam;

private:
    //==============================================================================
	template <typename FloatType>
	void process(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer);
	template <typename FloatType>
	void applyGain(AudioBuffer<FloatType>&, AudioBuffer<FloatType>& delayBuffer);
	template <typename FloatType>
	void applyDelay(AudioBuffer<FloatType>&, AudioBuffer<FloatType>& delayBuffer);
	template <typename FloatType>
	void applyFilter(AudioBuffer<FloatType>&, AudioBuffer<FloatType>& delayBuffer);

	AudioBuffer<float> delayBufferFloat;
	AudioBuffer<double> delayBufferDouble;
	int delayPosition;
	double currentSampleRate = 0;

	Synthesiser synth;
	// Contains filters for left and right channel
	std::vector<IIRFilter> filters;

	void initialiseSynthForWaveform(const Waveform waveform, const int numVoices);
	void initialiseLowPassFilter();
	void updateCurrentTimeInfoFromHost();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoisemakerAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
