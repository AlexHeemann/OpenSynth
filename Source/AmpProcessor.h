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
    AmpProcessor() {};
    virtual ~AmpProcessor() {};
    
    template <typename FloatType>
    void process(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer);
    void setEnvelopeGenerator(EnvelopeGenerator* envelopeGenerator);
    EnvelopeGenerator* getEnvelopeGenerator();
    void setLevel(float level);
    float getLevel();
    
private:
    EnvelopeGenerator* envelopeGenerator;
    float level;
    
};



#endif  // AMPPROCESSOR_H_INCLUDED
