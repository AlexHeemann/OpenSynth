/*
  ==============================================================================

    WavetableVoice.h
    Created: 6 Oct 2016 9:35:15am
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef WAVETABLEVOICE_H_INCLUDED
#define WAVETABLEVOICE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Wavetable.h"
#include "EnvelopeGenerator.h"
#include "AmpProcessor.h"
#include "FilterProcessor.h"

class WavetableSound : public SynthesiserSound
{
public:
    WavetableSound() {}
    
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

//==============================================================================
class WavetableVoice : public SynthesiserVoice
{
public:
    WavetableVoice(Wavetable* wavetable);
    virtual ~WavetableVoice();
    
    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast<WavetableSound*> (sound) != nullptr;
    }
    
    void startNote(int midiNoteNumber, float velocity,
                   SynthesiserSound* sound,
                   int currentPitchWheelPosition) override;
    
    void stopNote(float velocity, bool allowTailOff) override;
    
    void pitchWheelMoved(int newValue) override {}
    
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override {}
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBlock(outputBuffer, startSample, numSamples);
    }
    
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBlock(outputBuffer, startSample, numSamples);
    }
    
    void setAmpEnvelopeGenerator(EnvelopeGenerator* ampEnvelopeGenerator);
    EnvelopeGenerator* getAmpEnvelopeGenerator() const { return ampEnvelopeGenerator; };
    void setFilterEnvelopeGenerator(EnvelopeGenerator* filterEnvelopeGenerator);
    EnvelopeGenerator* getFilterEnvelopeGenerator() const { return filterEnvelopeGenerator; };
    
    /**
     * Set the wavetable to use for the voice
     */
    void setOsc1Wavetable(Wavetable* wavetable);
    void setOsc2Wavetable(Wavetable* wavetable);
    
    AmpProcessor& getAmpProcessor() { return ampProcessor; }
    FilterProcessor& getFilterProcessor() { return filterProcessor; }
    
    AudioParameterInt* osc1Semi;
    AudioParameterInt* osc2Semi;
    AudioParameterInt* osc1Cents;
    AudioParameterInt* osc2Cents;
    AudioParameterFloat* oscMix;
    
private:
    double currentPhase1, currentPhase2, phaseIncrement1, phaseIncrement2, level, frequency1, frequency2, frqRad;
    Wavetable* osc1Wavetable;
    Wavetable* osc2Wavetable;
    EnvelopeGenerator* ampEnvelopeGenerator;
    EnvelopeGenerator* filterEnvelopeGenerator;
    
    // Processors
    AmpProcessor ampProcessor;
    FilterProcessor filterProcessor;
    
    int releaseCounter;
    
    template <typename FloatType>
    void processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples);
    
    void calculatePhaseIncrement();
};



#endif  // WAVETABLEVOICE_H_INCLUDED
