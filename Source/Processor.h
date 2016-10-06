/*
  ==============================================================================

    Processor.h
    Created: 6 Oct 2016 2:34:51pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Processor
{
public:
    Processor() {};
    virtual ~Processor() {};
    
    virtual void process(AudioBuffer<float>& buffer, MidiBuffer& midiMessages, AudioBuffer<float>& delayBuffer) = 0;
    virtual void process(AudioBuffer<double>& buffer, MidiBuffer& midiMessages, AudioBuffer<double>& delayBuffer) = 0;
};


#endif  // PROCESSOR_H_INCLUDED
