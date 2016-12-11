/*
  ==============================================================================

    OscillatorParameterContainer.h
    Created: 4 Dec 2016 7:38:00pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef OSCILLATORPARAMETERCONTAINER_H_INCLUDED
#define OSCILLATORPARAMETERCONTAINER_H_INCLUDED

#include "ParameterContainer.h"
#include "PluginProcessor.h"

class OscillatorParameterContainer: public ParameterContainer
{
public:
    
    OscillatorParameterContainer(OpenSynthAudioProcessor& processor) : processor(processor)
    {
        processor.addParameter(osc1Semi = new AudioParameterInt("osc1semi", "Osc 1 Semi", -36, 36, 0));
        processor.addParameter(osc2Semi = new AudioParameterInt("osc2semi", "Osc 2 Semi", -36, 36, 0));
        processor.addParameter(osc1Cents = new AudioParameterInt("osc1cents", "Osc 1 Cents", -30, 30, 0));
        processor.addParameter(osc2Cents = new AudioParameterInt("osc2cents", "Osc 2 Cents", -30, 30, 0));
        processor.addParameter(oscMix = new AudioParameterFloat("oscMix", "Osc Mix", 0.0f, 1.0f, 0.0f));
        processor.addParameter(osc1Waveform = new AudioParameterChoice("osc1Waveform", "Osc 1 Waveform", waveforms, WaveformSawtooth));
        processor.addParameter(osc2Waveform = new AudioParameterChoice("osc2Waveform", "Osc 2 Waveform", waveforms, WaveformSawtooth));
    }
    
    virtual ~OscillatorParameterContainer() {}
    
    AudioParameterFloat* getOscMixParameter() const { return oscMix; }
    AudioParameterInt* getOsc1SemiParameter() const { return osc1Semi; }
    AudioParameterInt* getOsc2SemiParameter() const { return osc2Semi; }
    AudioParameterInt* getOsc1Cents() const { return osc1Cents; }
    AudioParameterInt* getOsc2Cents() const { return osc2Cents; }
    AudioParameterChoice* getOsc1Waveform() const { return osc1Waveform; }
    AudioParameterChoice* getOsc2Waveform() const { return osc2Waveform; }
    
    void setWaveformForOscillator(Waveform waveform, int oscillator)
    {
        processor.setWaveformForOscillator(waveform, oscillator);
    }
    
private:
    OpenSynthAudioProcessor& processor;
    
    AudioParameterFloat* oscMix;
    AudioParameterInt* osc1Semi;
    AudioParameterInt* osc2Semi;
    AudioParameterInt* osc1Cents;
    AudioParameterInt* osc2Cents;
    AudioParameterChoice* osc1Waveform;
    AudioParameterChoice* osc2Waveform;
    StringArray waveforms = {"Sine", "Sawtooth", "Square", "Triangle"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorParameterContainer)
};



#endif  // OSCILLATORPARAMETERCONTAINER_H_INCLUDED
