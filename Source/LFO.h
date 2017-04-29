/*
  ==============================================================================

    LFO.h
    Created: 24 Apr 2017 9:55:03am
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef LFO_H_INCLUDED
#define LFO_H_INCLUDED

#include "JuceHeader.h"
#include "Module.h"
#include <set>

class ModulationMatrix;

class LFO : public Module
{
public:
    
    typedef enum
    {
        LFOWaveformSine,
        LFOWaveformSaw,
        LFOWaveformSquare,
        LFOWaveformTriangle,
    } LFOWaveform;
    
    LFO(int ID, AudioProcessor& processor) : Module(ID, processor)
    {
        processor.addParameter(phaseOffsetParameter = new AudioParameterFloat(std::to_string(ID) + "_" + "phaseOffset", "Phase Offset", 0.0f, 1.0f, 0.0f));
        processor.addParameter(frequencyParameter = new AudioParameterFloat(std::to_string(ID) + "_" + "frequencyParameter", "Frequency", 0.0f, 20.0f, 10.0f));
    };
    ~LFO() {};
    
    double getCurrentValue() { return currentValue; }
    void setSampleRate(int sampleRate)
    {
        this->sampleRate = sampleRate;
        frqRad = (2.0 * double_Pi) / sampleRate;
    };
    AudioParameterFloat* phaseOffsetParameter;
    AudioParameterFloat* frequencyParameter;
    
    // Calculates the next values for the LFO
    void oscillate(int numSamples);
    void reset();
    
    void addTarget(int targetID);
    void removeTarget(int targetID);
    
private:
    std::set<int> targets;
    LFOWaveform waveform = LFOWaveformSine;
    double currentValue = 0;
    double currentPhase = 0;
    double phaseIncrement;
    double frqRad;
    int sampleRate;
    
    void calculatePhaseIncrement();
    
};



#endif  // LFO_H_INCLUDED
