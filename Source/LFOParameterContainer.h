/*
  ==============================================================================

    LFOParameterContainer.h
    Created: 2 May 2017 9:02:42pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef LFOPARAMETERCONTAINER_H_INCLUDED
#define LFOPARAMETERCONTAINER_H_INCLUDED

#include "ModulationParameterContainer.h"

class LFOParameterContainer : public ModulationParameterContainer
{
public:
    LFOParameterContainer(int ID, OpenSynthAudioProcessor& processor) : ModulationParameterContainer(ID, processor)
    {
        frequencyParameterID = processor.getIDManager().getNewID();
        
        processor.addParameter(phaseOffsetParameter = new AudioParameterFloat("LFO_" + String(ID) + "_phaseOffset", "LFO " + String(ID) + " Phase Offset", 0.0f, 1.0f, 0.0f));
        processor.addParameter(frequencyParameter = new AudioParameterFloat("LFO_" + String(ID) + "_frequency", "LFO " + String(ID) + " Frequency", 0.0f, 20.0f, 5.0f));
        processor.addParameter(waveformParameter = new AudioParameterChoice("LFO_" + String(ID) + "_waveform", "LFO " + String(ID) + " Waveform", waveforms, WaveformSine));
    };
    
    virtual ~LFOParameterContainer() {};
    
    const int getFrequencyParameterID() const { return frequencyParameterID; }
    
    AudioParameterFloat* getPhaseOffsetParameter() const { return phaseOffsetParameter; }
    AudioParameterFloat* getFrequencyParameter() const { return frequencyParameter; }
    AudioParameterChoice* getWaveformParameter() const { return waveformParameter; }
    void setWaveform(Waveform waveform)
    {
        *waveformParameter = waveform;
    }
    
private:
    int frequencyParameterID = 0;
    
    AudioParameterFloat* phaseOffsetParameter;
    AudioParameterFloat* frequencyParameter;
    AudioParameterChoice* waveformParameter;
    StringArray waveforms = {"Sine", "Sawtooth", "Square", "Triangle"};
};


#endif // PARAMETERCONTAINER_H_INCLUDED

