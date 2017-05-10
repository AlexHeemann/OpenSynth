/*
  ==============================================================================

    ModulationParameterContainer.h
    Created: 9 May 2017 9:31:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include "ParameterContainer.h"

class ModulationParameterContainer : public ParameterContainer
{
public:
    ModulationParameterContainer(AudioProcessor& processor, String name) : processor(processor)
    {
        processor.addParameter(modulationAmountParameter = new AudioParameterFloat(name + "modulation_amount", name + "Modulation Amount", 0.0f, 1.0f, 0.5f));
    }
    
    virtual ~ModulationParameterContainer() {}
    
    AudioParameterFloat* getModulationAmountParameter() const { return modulationAmountParameter; }
    
    void setID(int ID) { this->ID = ID; }
    int getID() { return ID; }
    
protected:
    AudioProcessor& processor;
    AudioParameterFloat* modulationAmountParameter;
    
    int ID = 0;
};
