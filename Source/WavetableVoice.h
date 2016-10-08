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
    WavetableVoice(Wavetable& wavetable);
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
    
    void setEnvelopeGenerator(EnvelopeGenerator *envelopeGenerator);
    EnvelopeGenerator* getEnvelopeGenerator() const { return envelopeGenerator; };
    
    /**
     * Set the wavetable to use for the voice
     */
    void setWavetable(Wavetable& wavetable);
    
    AmpProcessor& getAmpProcessor() { return ampProcessor; }
    
private:
    
    template <typename FloatType>
    void processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples);
    double currentPhase, phaseIncrement, level, frequency;
    Wavetable& wavetable;
    EnvelopeGenerator* envelopeGenerator;
    AmpProcessor ampProcessor;
    int releaseCounter;
};



#endif  // WAVETABLEVOICE_H_INCLUDED
