/*
  ==============================================================================

    TriangleWave.h
    Created: 15 May 2016 2:55:57pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef TRIANGLEWAVE_H_INCLUDED
#define TRIANGLEWAVE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class TriangleWaveSound : public SynthesiserSound
{
public:
    TriangleWaveSound() {}
    
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */
class TriangleWaveVoice : public SynthesiserVoice
{
public:
    TriangleWaveVoice()
    : angleDelta(0.0),
    tailOff(0.0)
    {
    }
    
    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast<TriangleWaveSound*> (sound) != nullptr;
    }
    
    void startNote(int midiNoteNumber, float velocity,
                   SynthesiserSound* /*sound*/,
                   int /*currentPitchWheelPosition*/) override
    {
        phase = 0.0;
        level = velocity * 0.15;
        tailOff = 0.0;
        
        double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        double cyclesPerSample = cyclesPerSecond / getSampleRate();
        double frqRad = (2.0 * double_Pi) / getSampleRate();
        twoDivPi = 2.0 / double_Pi;
        twoPi = 2.0 * double_Pi;
        frequency = cyclesPerSecond;
        period = 1 / frequency;
        
        angleDelta = frqRad * frequency;
    }
    
    void stopNote(float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.
            
            if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
                // stopNote method could be called more than once.
                tailOff = 1.0;
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..
            
            clearCurrentNote();
            angleDelta = 0.0;
        }
    }
    
    void pitchWheelMoved(int /*newValue*/) override
    {
        // can't be bothered implementing this for the demo!
    }
    
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override
    {
        // not interested in controllers in this case.
    }
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBlock(outputBuffer, startSample, numSamples);
    }
    
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBlock(outputBuffer, startSample, numSamples);
    }
    
private:
    
    template <typename FloatType>
    void processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples)
    {
        if (angleDelta != 0.0)
        {
            if (tailOff > 0)
            {
                while (--numSamples >= 0)
                {
                    double triValue = phase * twoDivPi;
                    if (phase < 0)
                    {
                        triValue = 1 + triValue;
                    }
                    else
                    {
                        triValue = 1 - triValue;
                    }
                    FloatType currentSample = level * triValue;
                    
                    for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample(i, startSample, currentSample);
                    
                    phase += angleDelta;
                    if (phase >= double_Pi)
                    {
                        phase -= twoPi;
                    }
                    ++startSample;
                    
                    tailOff *= 0.99;
                    
                    if (tailOff <= 0.005)
                    {
                        clearCurrentNote();
                        
                        angleDelta = 0.0;
                        break;
                    }
                }
            }
            else
            {
                while (--numSamples >= 0)
                {
                    double triValue = phase * twoDivPi;
                    if (phase < 0)
                    {
                        triValue = 1 + triValue;
                    }
                    else
                    {
                        triValue = 1 - triValue;
                    }
                    FloatType currentSample = level * triValue;
                    
                    for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample(i, startSample, currentSample);
                    
                    phase += angleDelta;
                    if (phase >= double_Pi)
                    {
                        phase -= twoPi;
                    }
                    ++startSample;
                }
            }
        }
    }
    
    double phase, angleDelta, level, tailOff, frequency, period, twoDivPi, twoPi;
};



#endif  // TRIANGLEWAVE_H_INCLUDED
