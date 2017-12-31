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
    
    struct Constants
    {
        struct Identifiers
        {
            static const String LFO;
            static const String Frequency;
            static const String PhaseOffset;
            static const String Waveform;
        };
        struct Names
        {
            static const String LFO;
            static const String Frequency;
            static const String PhaseOffset;
            static const String Waveform;
        };
    };
    
    LFO(int ID,
        ModulationMatrix *modulationMatrix,
        AudioProcessorValueTreeState& audioProcessorValueTreeState,
        IDManager& idManager,
        int sampleRate);
    ~LFO() {};
    
    double getCurrentValue() const { return currentValue; }
    void setSampleRate(int sampleRate) override
    {
        this->sampleRate = sampleRate;
        frqRad = (2.0 * double_Pi) / sampleRate;
    };
    
    // Calculates the next values for the LFO
    void calculateModulation(int numSamples) override;
    void reset() override;
    
    void addTarget(int targetID);
    void removeTarget(int targetID);
    
    int getFrequencyParameterID() const { return frequencyParameterID; }
    int getPhaseOffsetParameterID() const { return phaseOffsetParameterID; }
    int getWaveformParameterID() const { return waveformParameterID; }
    
private:
    std::set<int> targets;
    double currentPhase = 0.0;
    double phaseIncrement;
    double frqRad;
    int sampleRate;
    
    String frequencyParameterStringID();
    String phaseOffsetParameterStringID();
    String waveformParameterStringID();
    String stringIdentifier() const override;
    
    int frequencyParameterID;
    int phaseOffsetParameterID;
    int waveformParameterID;
    
    void calculatePhaseIncrement();
    
};



#endif  // LFO_H_INCLUDED
