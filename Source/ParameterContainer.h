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

class ParameterContainer
{
public:
    virtual ~ParameterContainer() {};
    virtual const std::vector<AudioProcessorParameter>& getParameters() const { return parameters; };
    
protected:
    std::vector<AudioProcessorParameter> parameters;
};



#endif  // PARAMETERCONTAINER_H_INCLUDED
