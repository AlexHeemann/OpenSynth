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
#include "Waveform.h"

class OscillatorParameterContainer: public ParameterContainer
{
public:
    
    OscillatorParameterContainer(int ID,
                                 OpenSynth& synth,
                                 OpenSynthAudioProcessor& processor) : ParameterContainer(ID,
                                                                                          synth,
                                                                                          processor)
    {
        gainParameterID = synth.getIDManager().getNewID();
        semiParameterID = synth.getIDManager().getNewID();
        centsParameterID = synth.getIDManager().getNewID();
        waveformParameterID = synth.getIDManager().getNewID();
        
        processor.addParameter(semi = new AudioParameterInt("oscSemi" + String(semiParameterID), "Osc Semi", -36, 36, 0));
        processor.addParameter(cents = new AudioParameterInt("oscCents" + String(centsParameterID), "Osc Cents", -30, 30, 0));
        processor.addParameter(gain = new AudioParameterFloat("oscGain" + String(gainParameterID), "Osc Gain", 0.0f, 1.0f, 0.6f));
        processor.addParameter(waveformParameter = new AudioParameterChoice("oscWaveform" + String(waveformParameterID), "Osc Waveform", waveforms, WaveformSawtooth));
    }
    
    virtual ~OscillatorParameterContainer() {}
    
    int getGainParameterID() const { return gainParameterID; }
    int getSemiParameterID() const { return semiParameterID; }
    int getCentsParameterID() const { return centsParameterID; }
    int getWaveformParameterID() const { return waveformParameterID; }
    
    AudioParameterFloat* getGainParameter() const { return gain; }
    AudioParameterInt* getSemiParameter() const { return semi; }
    AudioParameterInt* getCentsParameter() const { return cents; }
    AudioParameterChoice* getWaveformParameter() const { return waveformParameter; }
    
    Waveform getWaveform() const { return waveform; }
    void setWaveform(Waveform waveform) { this->waveform = waveform; }
    
    OpenSynthAudioProcessor& getProcessor() { return processor; }    
    
private:
    int gainParameterID;
    int semiParameterID;
    int centsParameterID;
    int waveformParameterID;
    
    AudioParameterFloat* gain;
    AudioParameterInt* semi;
    AudioParameterInt* cents;
    AudioParameterChoice* waveformParameter;
    Waveform waveform = WaveformSine;
    StringArray waveforms = {"Sine", "Sawtooth", "Square", "Triangle"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorParameterContainer)
};



#endif  // OSCILLATORPARAMETERCONTAINER_H_INCLUDED
