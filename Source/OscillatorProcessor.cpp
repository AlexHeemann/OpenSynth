/*
  ==============================================================================

    OscillatorProcessor.cpp
    Created: 7 Aug 2017 6:58:17pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "OscillatorProcessor.h"
#include "OscillatorParameterContainer.h"
#include "Utility.h"
#include "ModulationMatrix.h"

OscillatorProcessor::OscillatorProcessor(ModulationMatrix* modulationMatrix,
                                         int bufferSize,
                                         int sampleRate) :
Processor(modulationMatrix, bufferSize),
sampleRate(sampleRate)
{
    calculateFrqRad();
}

void OscillatorProcessor::calculateFrqRad()
{
    frqRad = (2.0 * double_Pi) / sampleRate;
}

void OscillatorProcessor::renderNextBlock()
{
    audioBuffer.clear();
    processBuffer(audioBuffer, 0, audioBuffer.getNumSamples());
}

template <typename FloatType>
void OscillatorProcessor::processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples)
{
    if (hasProcessed || currentNote < 0) return;
    
    Range<int> semiRange = parameterContainer->getSemiParameter()->getRange();
    
    float semiModulation = semiRange.getEnd() * modulationMatrix->getValueForDestinationID(parameterContainer->getSemiParameterID());
    int oscNote = currentNote + parameterContainer->getSemiParameter()->get();
    
    Range<int> centsRange = parameterContainer->getCentsParameter()->getRange();
    float centsModulation = centsRange.getEnd() * modulationMatrix->getValueForDestinationID(parameterContainer->getCentsParameterID());
    
    frequency = getFrequencyFromFloatNote(oscNote + semiModulation + ((parameterContainer->getCentsParameter()->get() + centsModulation)/100.0));
    calculatePhaseIncrement();
    
    if (phaseIncrement != 0.0)
    {
        float* subtable = wavetable->getSubtableForFrequency(frequency);
        int tableSize = wavetable->getTableSize();
        const float level = parameterContainer->getGainParameter()->get();
        
        double twoPi = 2.0 * double_Pi;
        if (releaseCounter > 0)
        {
            for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
            {
                int index = (int)((currentPhase / twoPi) * tableSize);
                // Interpolate for better accuracy
                float indexFractional = ((currentPhase / twoPi) * tableSize) - index;
                FloatType currentSample = level * (subtable[index] + ((subtable[(index + 1) % tableSize] - subtable[index]) * indexFractional));                
                
                for (int channel = 0; channel < buffer.getNumChannels(); channel++)
                {
                    buffer.setSample(channel, sampleIdx, currentSample);
                }
                
                currentPhase += phaseIncrement;
                if (currentPhase >= twoPi)
                {
                    currentPhase -= twoPi;
                }
                releaseCounter--;
                
                if (releaseCounter <= 0)
                {
                    phaseIncrement = 0.0;
                    currentPhase = 0.0;
                    break;
                }
            }
        }
        else
        {
            for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
            {
                int index = (int)((currentPhase / twoPi) * tableSize);
                FloatType currentSample = level * subtable[index];
                
                for (int channel = 0; channel < buffer.getNumChannels(); channel++)
                {
                    buffer.setSample(channel, sampleIdx, currentSample);
                }
                
                currentPhase += phaseIncrement;
                if (currentPhase >= twoPi)
                {
                    currentPhase -= twoPi;
                }
            }
        }
    }
}

void OscillatorProcessor::calculatePhaseIncrement()
{
    phaseIncrement = frqRad * frequency;
}

void OscillatorProcessor::reset()
{
    phaseIncrement = 0.0;
    currentPhase = 0.0;
}
