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
    
    virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, AudioBuffer<float>& delayBuffer, int startSample, int numSamples) = 0;
    virtual void renderNextBlock(AudioBuffer<double>& outputBuffer, AudioBuffer<double>& delayBuffer, int startSample, int numSamples) = 0;
};


#endif  // PROCESSOR_H_INCLUDED
