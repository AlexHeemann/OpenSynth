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

class LFOParameterContainer;

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
    
    LFO(int ID, LFOParameterContainer* parameterContainer) : Module(ID), parameterContainer(parameterContainer)
    {
    };
    ~LFO() {};
    
    double getCurrentValue() const { return currentValue; }
    void setSampleRate(int sampleRate)
    {
        this->sampleRate = sampleRate;
        frqRad = (2.0 * double_Pi) / sampleRate;
    };
    
    LFOParameterContainer* getParameterContainer() const { return parameterContainer; }
    
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
    LFOParameterContainer* parameterContainer;
    
    void calculatePhaseIncrement();
    
};



#endif  // LFO_H_INCLUDED
