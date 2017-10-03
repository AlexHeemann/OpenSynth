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
    
    LFO(LFOParameterContainer* parameterContainer);
    ~LFO() {};
    
    double getCurrentValue() const { return currentValue; }
    void setSampleRate(int sampleRate) override
    {
        this->sampleRate = sampleRate;
        frqRad = (2.0 * double_Pi) / sampleRate;
    };
    
    LFOParameterContainer* getParameterContainer() const { return parameterContainer; }
    
    // Calculates the next values for the LFO
    void calculateModulation(int numSamples) override;
    void reset() override;
    
    void addTarget(int targetID);
    void removeTarget(int targetID);
    
private:
    std::set<int> targets;
    double currentPhase = 0.0;
    double phaseIncrement;
    double frqRad;
    int sampleRate;
    LFOParameterContainer* parameterContainer;
    
    void calculatePhaseIncrement();
    
};



#endif  // LFO_H_INCLUDED
