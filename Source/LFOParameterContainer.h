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
#include "PluginProcessor.h"

class LFOParameterContainer : public ModulationParameterContainer
{
public:
    LFOParameterContainer(AudioProcessor& processor, String name) : ModulationParameterContainer(processor, name)
    {
        processor.addParameter(phaseOffsetParameter = new AudioParameterFloat("LFO_phaseOffset", "Phase Offset", 0.0f, 1.0f, 0.0f));
        processor.addParameter(frequencyParameter = new AudioParameterFloat("LFO_frequency", "Frequency", 0.0f, 20.0f, 5.0f));
        processor.addParameter(waveformParameter = new AudioParameterChoice("LFO_waveform", "Waveform", waveforms, WaveformSine));
    };
    
    virtual ~LFOParameterContainer() {};
    
    AudioParameterFloat* getPhaseOffsetParameter() const { return phaseOffsetParameter; }
    AudioParameterFloat* getFrequencyParameter() const { return frequencyParameter; }
    AudioParameterChoice* getWaveformParameter() const { return waveformParameter; }
    void setWaveform(Waveform waveform)
    {
        *waveformParameter = waveform;
    }
    
private:
    AudioParameterFloat* phaseOffsetParameter;
    AudioParameterFloat* frequencyParameter;
    AudioParameterChoice* waveformParameter;
    StringArray waveforms = {"Sine", "Sawtooth", "Square", "Triangle"};
};


#endif // PARAMETERCONTAINER_H_INCLUDED

