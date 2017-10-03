/*
  ==============================================================================

    OscillatorProcessor.h
    Created: 7 Aug 2017 6:58:17pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include "Processor.h"
#include "Wavetable.h"

class OscillatorParameterContainer;

class OscillatorProcessor : public Processor
{
public:
    OscillatorProcessor(ModulationMatrix* modulationMatrix, int bufferSize, int sampleRate);
    virtual ~OscillatorProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock() override;
    
    void setWavetable(Wavetable* wavetable)
    {
        this->wavetable = wavetable;
    }
    
    void setNote(int note)
    {
        this->currentNote = note;
    }
    
    void setSampleRate(int sampleRate)
    {
        this->sampleRate = sampleRate;
        calculateFrqRad();
    }
    
    void setParameterContainer(OscillatorParameterContainer* parameterContainer) { this->parameterContainer = parameterContainer; };
    OscillatorParameterContainer* getParameterContainer() { return parameterContainer; }
    
    void reset() override;
    
private:
    double currentPhase, phaseIncrement, level, frequency, frqRad = 0.0f;
    Wavetable* wavetable;
    int releaseCounter = 0;
    int sampleRate = 0;
    int currentNote = -1;
    
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
    void calculatePhaseIncrement();
    void calculateFrqRad();
    
    OscillatorParameterContainer* parameterContainer;
};
