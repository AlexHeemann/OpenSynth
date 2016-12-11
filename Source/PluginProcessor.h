/*
  ==============================================================================

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
#include "DelayProcessor.h"
#include "ReverbProcessor.h"
#include "FilterProcessor.h"

class ReverbParameterContainer;
class EnvelopeParameterContainer;
class OscillatorParameterContainer;
class FilterParameterContainer;

typedef enum
{
    WaveformSine,
    WaveformSawtooth,
    WaveformSquare,
    WaveformTriangle,
} Waveform;

//==============================================================================
/**
*/
class OpenSynthAudioProcessor  : public AudioProcessor, private MidiKeyboardStateListener
{
public:
    //==============================================================================
    OpenSynthAudioProcessor();
    ~OpenSynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
	void reset() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

	//==============================================================================
	void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override
	{
		jassert(!isUsingDoublePrecision());
		process(buffer, midiMessages);
	}

	void processBlock(AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override
	{
		jassert(isUsingDoublePrecision());
		process(buffer, midiMessages);
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

    void setFilterType(FilterProcessor::FilterType filterType);
    void setWaveformForOscillator(Waveform waveform, int oscillator);

	// this is kept up to date with the midi messages that arrive, and the UI component
	// registers with it so it can represent the incoming messages
	MidiKeyboardState keyboardState;

	// Gain parameters
    AudioParameterFloat* level;    
    
    // Delay Parameters
    AudioParameterFloat* delayTime;
    AudioParameterFloat* delayFeedback;
    AudioParameterFloat* delaySpread;
    AudioParameterFloat* delayMix;
    AudioParameterBool* delayEnabled;
    
    
    ReverbParameterContainer& getReverbParameterContainer()
    {
        return *reverbParameterContainer;
    }
    EnvelopeParameterContainer& getFilterEnvelopeParameterContainer()
    {
        return *filterEnvelopeParameterContainer;
    }
    EnvelopeParameterContainer& getAmpEnvelopeParameterContainer()
    {
        return *ampEnvelopeParameterContainer;
    }
    OscillatorParameterContainer& getOscillatorParameterContainer()
    {
        return *oscillatorParameterContainer;
    }
    FilterParameterContainer& getFilterParameterContainer()
    {
        return *filterParameterContainer;
    }
    

private:
    //==============================================================================
	template <typename FloatType>
	void process(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages);
	
	double currentSampleRate = 0;

	Synthesiser synth;
    SawtoothWavetable sawtoothWavetable;
    SquareWavetable squareWavetable;
    SineWavetable sineWavetable;
    
    DelayProcessor delayProcessor;
    ReverbProcessor reverbProcessor;
    
    ScopedPointer<ReverbParameterContainer> reverbParameterContainer;
    ScopedPointer<EnvelopeParameterContainer> filterEnvelopeParameterContainer;
    ScopedPointer<EnvelopeParameterContainer> ampEnvelopeParameterContainer;
    ScopedPointer<OscillatorParameterContainer> oscillatorParameterContainer;
    ScopedPointer<FilterParameterContainer> filterParameterContainer;

	void initialiseSynthForWaveform(const Waveform waveform, const int numVoices);

	virtual void handleNoteOn(MidiKeyboardState* source,
		int midiChannel, int midiNoteNumber, float velocity) override;
	virtual void handleNoteOff(MidiKeyboardState* source,
		int midiChannel, int midiNoteNumber, float velocity) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenSynthAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
