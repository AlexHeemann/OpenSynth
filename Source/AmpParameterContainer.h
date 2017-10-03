/*
  ==============================================================================

    AmpParameterContainer.h
    Created: 4 Dec 2016 7:37:46pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef AMPPARAMETERCONTAINER_H_INCLUDED
#define AMPPARAMETERCONTAINER_H_INCLUDED

#include "ParameterContainer.h"

class AmpParameterContainer: public ParameterContainer
{
public:
    AmpParameterContainer(int ID, OpenSynthAudioProcessor& processor) : ParameterContainer(ID, processor)
    {
        gainParameterID = processor.getIDManager().getNewID();
        
        processor.addParameter(gain = new AudioParameterFloat("Amp Gain", "Amp Gain", 0.0, 1.0, 0.6));
    }
    
    ~AmpParameterContainer() {}
    
    const int getGainParameterID() const { return gainParameterID; }
    
    AudioParameterFloat* getGainParameter() const { return gain; }
    
private:
    int gainParameterID = 0;
        
    AudioParameterFloat* gain;
};



#endif  // AMPPARAMETERCONTAINER_H_INCLUDED
