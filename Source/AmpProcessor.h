/*
  ==============================================================================

    AmpProcessor.h
    Created: 6 Oct 2016 2:33:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef AMPPROCESSOR_H_INCLUDED
#define AMPPROCESSOR_H_INCLUDED

#include "Processor.h"
#include "EnvelopeGenerator.h"

class AmpProcessor : public Processor
{
public:
    AmpProcessor();
    virtual ~AmpProcessor() {};
    
    void process(AudioBuffer<float>& buffer, MidiBuffer& midiMessages, AudioBuffer<float>& delayBuffer)
    {
        processBuffer(buffer, midiMessages, delayBuffer);
    }
    void process(AudioBuffer<double>& buffer, MidiBuffer& midiMessages, AudioBuffer<double>& delayBuffer)
    {
        processBuffer(buffer, midiMessages, delayBuffer);
    }
    
    void setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator);
    EnvelopeGenerator* getEnvelopeGenerator();
    AudioParameterFloat* level;
    
private:
    EnvelopeGenerator* envelopeGenerator;
    
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer);
};



#endif  // AMPPROCESSOR_H_INCLUDED
