/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeGenerator.h"
#include "DspFilters/Dsp.h"
#include "SawtoothWavetable.h"
#include "SquareWavetable.h"
#include "SineWavetable.h"
#include "AmpProcessor.h"

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
class NoisemakerAudioProcessor  : public AudioProcessor, private MidiKeyboardStateListener
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

	void setWaveformForOscillator(Waveform waveform, int oscillator);

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
    AudioParameterFloat* level;
    AudioParameterFloat* attackRateAmp;
    AudioParameterFloat* decayRateAmp;
    AudioParameterFloat* releaseRateAmp;
    AudioParameterFloat* sustainLevelAmp;
    AudioParameterFloat* attackRateFilter;
    AudioParameterFloat* decayRateFilter;
    AudioParameterFloat* releaseRateFilter;
    AudioParameterFloat* sustainLevelFilter;
    AudioParameterFloat* envelopeAmountFilter;
    AudioParameterFloat* filterFrequency;
    
    // Oscillator Parameters
    AudioParameterFloat* oscMix;
    AudioParameterInt* osc1Semi;
    AudioParameterInt* osc2Semi;
    AudioParameterInt* osc1Cents;
    AudioParameterInt* osc2Cents;

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
    SawtoothWavetable sawtoothWavetable;
    SquareWavetable squareWavetable;
    SineWavetable sineWavetable;
	// Contains filters for left and right channel
	std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::LowPass, 1>> filters;

	void initialiseSynthForWaveform(const Waveform waveform, const int numVoices);
	void initialiseLowPassFilter();
	void initialiseLowPassFilter(double frequency);
	void updateCurrentTimeInfoFromHost();

	virtual void handleNoteOn(MidiKeyboardState* source,
		int midiChannel, int midiNoteNumber, float velocity);
	virtual void handleNoteOff(MidiKeyboardState* source,
		int midiChannel, int midiNoteNumber, float velocity);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoisemakerAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
