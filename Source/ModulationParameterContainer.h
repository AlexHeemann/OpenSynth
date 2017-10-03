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
    ModulationParameterContainer(int ID, OpenSynthAudioProcessor& processor) : ParameterContainer(ID, processor)
    {
    }
    
    virtual ~ModulationParameterContainer() {}
    
    void setID(int ID) { this->ID = ID; }
    int getID() { return ID; }
};
