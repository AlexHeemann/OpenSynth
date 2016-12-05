
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "TriangleWave.h"
#include "WavetableVoice.h"
#include "ReverbParameterContainer.h"
#include "EnvelopeParameterContainer.h"

//==============================================================================
OpenSynthAudioProcessor::OpenSynthAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                ),
#endif
    sawtoothWavetable(SawtoothWavetable(40.0, 4096, getSampleRate())),
    squareWavetable(SquareWavetable(40.0, 4096, getSampleRate())),
    sineWavetable(SineWavetable(40.0, 4096, getSampleRate()))
{
	addParameter(level = new AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.9f));
    ampEnvelopeParameterContainer = new EnvelopeParameterContainer(*this, 1);
    filterEnvelopeParameterContainer = new EnvelopeParameterContainer(*this, 2);
    
    addParameter(filterFrequency = new AudioParameterFloat("filter_frequency", "Filter Frequency", 0.0f, 20000.0f, 10000.0f));
    filterFrequency->range.skew = 0.25;
    addParameter(envelopeAmountFilter = new AudioParameterFloat("env_amount_filter", "Envelope Amount", 0.0f, 1.0f, 0.0f));
     
    addParameter(attackRateFilter = new AudioParameterFloat("attack", "Envelope Attack", 0.0f, 3.0f, 1.0f));
    attackRateFilter->range.skew = 0.5;
    addParameter(decayRateFilter = new AudioParameterFloat("decay", "Envelope Decay", 0.0f, 3.0f, 1.0f));
    decayRateFilter->range.skew = 0.5;
    addParameter(releaseRateFilter = new AudioParameterFloat("release", "Envelope Release", 0.0f, 3.0f, 1.0f));
    releaseRateFilter->range.skew = 0.5;
    addParameter(sustainLevelFilter = new AudioParameterFloat("sustain", "Envelope Sustain", 0.0f, 1.0f, 1.0f));
    addParameter(filterResonance = new AudioParameterFloat("resonance", "Filter Resonance", 1.0f, 10.0f, 1.0f));
    
    addParameter(osc1Semi = new AudioParameterInt("osc1semi", "Osc 1 Semi", -36, 36, 0));
    addParameter(osc2Semi = new AudioParameterInt("osc2semi", "Osc 2 Semi", -36, 36, 0));
    addParameter(osc1Cents = new AudioParameterInt("osc1cents", "Osc 1 Cents", -30, 30, 0));
    addParameter(osc2Cents = new AudioParameterInt("osc2cents", "Osc 2 Cents", -30, 30, 0));
    addParameter(oscMix = new AudioParameterFloat("oscMix", "Osc Mix", 0.0f, 1.0f, 0.0f));
    
    // Delay
    addParameter(delayTime = new AudioParameterFloat("delayTime", "Delay Time", 0.0f, 1.0f, 0.5f));
    addParameter(delayFeedback = new AudioParameterFloat("delayFeedback", "Delay Feedback", 0.0f, 1.0f, 0.5f));
    addParameter(delaySpread = new AudioParameterFloat("delaySpread", "Delay Spread", 0.0f, 1.0f, 0.0f));
    addParameter(delayMix = new AudioParameterFloat("delayMix", "Delay Mix", 0.0f, 1.0f, 0.0f));
    addParameter(delayEnabled = new AudioParameterBool("delayEnabled", "Delay Enabled", false));
    
    delayProcessor.delayMix = delayMix;
    delayProcessor.delayTime = delayTime;
    delayProcessor.delayLevel = delayFeedback;
    delayProcessor.delaySpread = delaySpread;
    
    // Reverb
    reverbParameterContainer = new ReverbParameterContainer(*this);
    reverbProcessor.setReverbParameterContainer(reverbParameterContainer);
    
	initialiseSynthForWaveform(WaveformSawtooth, 8);
	keyboardState.addListener(this);
}

OpenSynthAudioProcessor::~OpenSynthAudioProcessor()
{
}

void OpenSynthAudioProcessor::initialiseSynthForWaveform(const Waveform waveform, const int numVoices)
{
	synth.clearSounds();
	synth.clearVoices();

	for (int i = numVoices; --i >= 0;)
	{
        WavetableVoice* wavetableVoice;
        switch (waveform)
        {
            case WaveformSine:
            {
                wavetableVoice = new WavetableVoice(&sineWavetable);
                break;
            }
            case WaveformSquare:
            {
                wavetableVoice = new WavetableVoice(&squareWavetable);
            }
                break;
            case WaveformSawtooth:
            {
                wavetableVoice = new WavetableVoice(&sawtoothWavetable);
            }
                break;
            case WaveformTriangle:
            {
                wavetableVoice = new WavetableVoice(&sawtoothWavetable);
            }
                break;
            default:
            {
                wavetableVoice = new WavetableVoice(&sawtoothWavetable);
            }
        }
        EnvelopeGenerator* ampEnvelopeGenerator = new EnvelopeGenerator();
        ampEnvelopeGenerator->setEnvelopeParameterContainer(ampEnvelopeParameterContainer);
        wavetableVoice->setAmpEnvelopeGenerator(ampEnvelopeGenerator);
    
        EnvelopeGenerator* filterEnvelopeGenerator = new EnvelopeGenerator();
        filterEnvelopeGenerator->setEnvelopeParameterContainer(filterEnvelopeParameterContainer);
        
        wavetableVoice->setFilterEnvelopeGenerator(filterEnvelopeGenerator);
        wavetableVoice->getAmpProcessor().level = level;
        wavetableVoice->getFilterProcessor().frequency = filterFrequency;
        wavetableVoice->getFilterProcessor().envelopeAmount = envelopeAmountFilter;
        wavetableVoice->getFilterProcessor().resonance = filterResonance;
        wavetableVoice->osc1Semi = osc1Semi;
        wavetableVoice->osc2Semi = osc2Semi;
        wavetableVoice->osc1Cents = osc1Cents;
        wavetableVoice->osc2Cents = osc2Cents;
        wavetableVoice->oscMix = oscMix;
        
        synth.addVoice(wavetableVoice);
	}

    synth.addSound(new WavetableSound());
}

//==============================================================================
const String OpenSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OpenSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OpenSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double OpenSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OpenSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OpenSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OpenSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String OpenSynthAudioProcessor::getProgramName (int index)
{
    return String();
}

void OpenSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void OpenSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    sawtoothWavetable.setSampleRate(sampleRate);
    squareWavetable.setSampleRate(sampleRate);
    sineWavetable.setSampleRate(sampleRate);
	synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int voiceIdx = 0; voiceIdx < synth.getNumVoices(); voiceIdx++)
    {
        WavetableVoice* voice = dynamic_cast<WavetableVoice*>(synth.getVoice(voiceIdx));
        if (voice != nullptr)
        {
            if (voice->getAmpEnvelopeGenerator() != nullptr)
            {
                voice->getAmpEnvelopeGenerator()->setSampleRate(sampleRate);
                voice->getAmpEnvelopeGenerator()->resetEnvelope();
            }
            if (voice->getAmpEnvelopeGenerator() != nullptr)
            {
                voice->getFilterEnvelopeGenerator()->setSampleRate(sampleRate);
                voice->getFilterEnvelopeGenerator()->resetEnvelope();
            }
        }
    }
	currentSampleRate = sampleRate;
	keyboardState.reset();
    delayProcessor.setIsUsingDoublePrecision(isUsingDoublePrecision());
    delayProcessor.setSampleRate(sampleRate);
    delayProcessor.reset();
    reverbProcessor.setSampleRate(sampleRate);
    reverbProcessor.reset();

	reset();
}

void OpenSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	keyboardState.reset();
}

void OpenSynthAudioProcessor::reset()
{
	// Use this method as the place to clear any delay lines, buffers, etc, as it
	// means there's been a break in the audio's continuity.
    delayProcessor.reset();
    reverbProcessor.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OpenSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

template <typename FloatType>
void OpenSynthAudioProcessor::process(AudioBuffer<FloatType>& buffer,
	MidiBuffer& midiMessages)
{
	const int numSamples = buffer.getNumSamples();

	// In case we have more outputs than inputs, we'll clear any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
		buffer.clear(i, 0, numSamples);

	// Now pass any incoming midi messages to our keyboard state object, and let it
	// add messages to the buffer if the user is clicking on the on-screen keys
	keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);

	// and now get our synth to process these midi events and generate its output.
	synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
    
    if (delayEnabled->get())
    {
        delayProcessor.renderNextBlock(buffer, 0, numSamples);
    }
    if (reverbParameterContainer->getReverbEnabledParameter()->get())
    {
        reverbProcessor.renderNextBlock(buffer, 0, numSamples);
    }
}

//==============================================================================
bool OpenSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* OpenSynthAudioProcessor::createEditor()
{
    return new OpenSynthAudioProcessorEditor (*this);
}

//==============================================================================
void OpenSynthAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// Here's an example of how you can use XML to make it easy and more robust:

	// Create an outer XML element..
	XmlElement xml("OpenSynthPluginSettings");

	// Store the values of all our parameters, using their param ID as the XML attribute
	for (int i = 0; i < getNumParameters(); ++i)
		if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
			xml.setAttribute(p->paramID, p->getValue());

	// then use this helper function to stuff it into the binary blob and return it..
	copyXmlToBinary(xml, destData);
}

void OpenSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.

	// This getXmlFromBinary() helper function retrieves our XML from the binary blob..
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
	{
		// make sure that it's actually our type of XML object..
		if (xmlState->hasTagName("OpenSynthPluginSettings"))
		{
			// Now reload our parameters..
			for (int i = 0; i < getNumParameters(); ++i)
				if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
					p->setValueNotifyingHost((float)xmlState->getDoubleAttribute(p->paramID, p->getValue()));
		}
	}
}

void OpenSynthAudioProcessor::setWaveformForOscillator(Waveform waveform, int oscillator)
{
    Wavetable* wavetable = nullptr;
    switch (waveform) {
        case WaveformSine:
            wavetable = &sineWavetable;
            break;
        case WaveformSawtooth:
            wavetable = &sawtoothWavetable;
            break;
        case WaveformSquare:
            wavetable = &squareWavetable;
            break;
        case WaveformTriangle:
            wavetable = &sineWavetable;
            break;
    }
    
    for (int voiceIdx = 0; voiceIdx < synth.getNumVoices(); voiceIdx++)
    {
        WavetableVoice* voice = dynamic_cast<WavetableVoice*>(synth.getVoice(voiceIdx));
        if (voice != nullptr)
        {
            if (oscillator == 1)
            {
                voice->setOsc1Wavetable(wavetable);
            }
            else if (oscillator == 2)
            {
                voice->setOsc2Wavetable(wavetable);
            }
        }
    }
}

void OpenSynthAudioProcessor::setFilterType(FilterProcessor::FilterType filterType)
{
    for (int voiceIdx = 0; voiceIdx < synth.getNumVoices(); voiceIdx++)
    {
        WavetableVoice* voice = dynamic_cast<WavetableVoice*>(synth.getVoice(voiceIdx));
        if (voice != nullptr)
        {
            voice->getFilterProcessor().setActiveFilter(filterType);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OpenSynthAudioProcessor();
}

//==============================================================================
// MidiKeyboardStateListener
void OpenSynthAudioProcessor::handleNoteOn(MidiKeyboardState* source,
	int midiChannel, int midiNoteNumber, float velocity)
{
	
}

void OpenSynthAudioProcessor::handleNoteOff(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity)
{
}
