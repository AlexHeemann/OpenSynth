/*
  ==============================================================================

    ParameterContainer.h
    Created: 4 Dec 2016 7:36:21pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef PARAMETERCONTAINER_H_INCLUDED
#define PARAMETERCONTAINER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class ParameterContainer
{
public:
    ParameterContainer(int ID, OpenSynthAudioProcessor& processor) : ID(ID), processor(processor)
    {
    }
    
    virtual ~ParameterContainer() {};
    virtual const std::vector<AudioProcessorParameter>& getParameters() const { return parameters; };
    
    const int getID() const { return ID; }
    void setID(const int ID) { this->ID = ID; }
    
protected:
    int ID;
    OpenSynthAudioProcessor& processor;
    std::vector<AudioProcessorParameter> parameters;
};



#endif  // PARAMETERCONTAINER_H_INCLUDED
