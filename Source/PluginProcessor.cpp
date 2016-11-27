
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "TriangleWave.h"
#include "WavetableVoice.h"

//==============================================================================
NoisemakerAudioProcessor::NoisemakerAudioProcessor() :
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
	lastUIWidth(600),
	lastUIHeight(260),
	delayPosition(0),
    sawtoothWavetable(SawtoothWavetable(40.0, 4096, getSampleRate())),
    squareWavetable(SquareWavetable(40.0, 4096, getSampleRate())),
    sineWavetable(SineWavetable(40.0, 4096, getSampleRate()))
{
    lastPosInfo.resetToDefault();
    
	// This creates our parameters. We'll keep some raw pointers to them in this class,
	// so that we can easily access them later, but the base class will take care of
	// deleting them for us.
	addParameter(level = new AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.9f));
    addParameter(attackRateAmp = new AudioParameterFloat("attack", "Envelope Attack", 0.0f, 3.0f, 0.0f));
    attackRateAmp->range.skew = 0.5;
    addParameter(decayRateAmp = new AudioParameterFloat("decay", "Envelope Decay", 0.0f, 3.0f, 3.0f));
    decayRateAmp->range.skew = 0.5;
    addParameter(releaseRateAmp = new AudioParameterFloat("release", "Envelope Release", 0.0f, 3.0f, 1.0f));
    releaseRateAmp->range.skew = 0.5;
    addParameter(sustainLevelAmp = new AudioParameterFloat("sustain", "Envelope Sustain", 0.0f, 1.0f, 1.0f));
    
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
    addParameter(reverbSize = new AudioParameterFloat("reverbSize", "Reverb Size", 0.0f, 1.0f, 0.5f));
    addParameter(reverbDamping = new AudioParameterFloat("reverbDamping", "Reverb Damping", 0.0f, 1.0f, 0.5f));
    addParameter(reverbDryLevel = new AudioParameterFloat("reverbDryLevel", "Reverb Dry Level", 0.0f, 1.0f, 0.4f));
    addParameter(reverbWetLevel = new AudioParameterFloat("reverbWetLevel", "Reverb Wet Level", 0.0f, 1.0f, 0.33f));
    addParameter(reverbWidth = new AudioParameterFloat("reverbWidth", "Reverb Width", 0.0f, 1.0f, 0.2f));
    addParameter(reverbEnabled = new AudioParameterBool("reverbEnabled", "Reverb Enabled", false));
    
    reverbProcessor.reverbSize = reverbSize;
    reverbProcessor.reverbDamping = reverbDamping;
    reverbProcessor.reverbDryLevel = reverbDryLevel;
    reverbProcessor.reverbWetLevel = reverbWetLevel;
    reverbProcessor.reverbWidth = reverbWidth;
    
	initialiseSynthForWaveform(WaveformSawtooth, 8);
	keyboardState.addListener(this);
}

NoisemakerAudioProcessor::~NoisemakerAudioProcessor()
{
}

void NoisemakerAudioProcessor::initialiseSynthForWaveform(const Waveform waveform, const int numVoices)
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
        ampEnvelopeGenerator->attackRate = attackRateAmp;
        ampEnvelopeGenerator->decayRate = decayRateAmp;
        ampEnvelopeGenerator->sustainLevel = sustainLevelAmp;
        ampEnvelopeGenerator->releaseRate = releaseRateAmp;
        wavetableVoice->setAmpEnvelopeGenerator(ampEnvelopeGenerator);
        EnvelopeGenerator* filterEnvelopeGenerator = new EnvelopeGenerator();
        filterEnvelopeGenerator->attackRate = attackRateFilter;
        filterEnvelopeGenerator->decayRate = decayRateFilter;
        filterEnvelopeGenerator->sustainLevel = sustainLevelFilter;
        filterEnvelopeGenerator->releaseRate = releaseRateFilter;
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
const String NoisemakerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoisemakerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoisemakerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double NoisemakerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoisemakerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NoisemakerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NoisemakerAudioProcessor::setCurrentProgram (int index)
{
}

const String NoisemakerAudioProcessor::getProgramName (int index)
{
    return String();
}

void NoisemakerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NoisemakerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
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

	if (isUsingDoublePrecision())
	{
		delayBufferDouble.setSize(2, 12000);
		delayBufferFloat.setSize(1, 1);
	}
	else
	{
		delayBufferFloat.setSize(2, 12000);
		delayBufferDouble.setSize(1, 1);
	}

	reset();
}

void NoisemakerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	keyboardState.reset();
}

void NoisemakerAudioProcessor::reset()
{
	// Use this method as the place to clear any delay lines, buffers, etc, as it
	// means there's been a break in the audio's continuity.
	delayBufferFloat.clear();
	delayBufferDouble.clear();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NoisemakerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
void NoisemakerAudioProcessor::process(AudioBuffer<FloatType>& buffer,
	MidiBuffer& midiMessages,
	AudioBuffer<FloatType>& delayBuffer)
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
    if (reverbEnabled->get())
    {
        reverbProcessor.renderNextBlock(buffer, 0, numSamples);
    }

	// Now ask the host for the current time so we can store it to be displayed later...
	updateCurrentTimeInfoFromHost();
}

template <typename FloatType>
void NoisemakerAudioProcessor::applyDelay(AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer)
{
	const int numSamples = buffer.getNumSamples();
	//const float delayLevel = delayParam->get();

	int delayPos = 0;

	for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
	{
		FloatType* const channelData = buffer.getWritePointer(channel);
		FloatType* const delayData = delayBuffer.getWritePointer(jmin(channel, delayBuffer.getNumChannels() - 1));
		delayPos = delayPosition;

		for (int i = 0; i < numSamples; ++i)
		{
			const FloatType in = channelData[i];
			channelData[i] += delayData[delayPos];
			//delayData[delayPos] = (delayData[delayPos] + in) * delayLevel;

			if (++delayPos >= delayBuffer.getNumSamples())
				delayPos = 0;
		}
	}

	delayPosition = delayPos;
}

void NoisemakerAudioProcessor::updateCurrentTimeInfoFromHost()
{
	if (AudioPlayHead* ph = getPlayHead())
	{
		AudioPlayHead::CurrentPositionInfo newTime;

		if (ph->getCurrentPosition(newTime))
		{
			lastPosInfo = newTime;  // Successfully got the current time from the host..
			return;
		}
	}

	// If the host fails to provide the current time, we'll just reset our copy to a default..
	lastPosInfo.resetToDefault();
}

//==============================================================================
bool NoisemakerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NoisemakerAudioProcessor::createEditor()
{
    return new NoisemakerAudioProcessorEditor (*this);
}

//==============================================================================
void NoisemakerAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// Here's an example of how you can use XML to make it easy and more robust:

	// Create an outer XML element..
	XmlElement xml("MYPLUGINSETTINGS");

	// add some attributes to it..
	xml.setAttribute("uiWidth", lastUIWidth);
	xml.setAttribute("uiHeight", lastUIHeight);

	// Store the values of all our parameters, using their param ID as the XML attribute
	for (int i = 0; i < getNumParameters(); ++i)
		if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
			xml.setAttribute(p->paramID, p->getValue());

	// then use this helper function to stuff it into the binary blob and return it..
	copyXmlToBinary(xml, destData);
}

void NoisemakerAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.

	// This getXmlFromBinary() helper function retrieves our XML from the binary blob..
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
	{
		// make sure that it's actually our type of XML object..
		if (xmlState->hasTagName("MYPLUGINSETTINGS"))
		{
			// ok, now pull out our last window size..
			lastUIWidth = xmlState->getIntAttribute("uiWidth", lastUIWidth);
			lastUIHeight = xmlState->getIntAttribute("uiHeight", lastUIHeight);

			// Now reload our parameters..
			for (int i = 0; i < getNumParameters(); ++i)
				if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
					p->setValueNotifyingHost((float)xmlState->getDoubleAttribute(p->paramID, p->getValue()));
		}
	}
}

void NoisemakerAudioProcessor::setWaveformForOscillator(Waveform waveform, int oscillator)
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

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoisemakerAudioProcessor();
}

//==============================================================================
// MidiKeyboardStateListener
void NoisemakerAudioProcessor::handleNoteOn(MidiKeyboardState* source,
	int midiChannel, int midiNoteNumber, float velocity)
{
	
}

void NoisemakerAudioProcessor::handleNoteOff(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity)
{
}
