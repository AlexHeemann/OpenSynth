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

// Parameter Strings
const String OscillatorProcessor::Constants::Identifiers::Semi = "semi";
const String OscillatorProcessor::Constants::Identifiers::Cents = "cents";
const String OscillatorProcessor::Constants::Identifiers::Gain = "gain";
const String OscillatorProcessor::Constants::Identifiers::Waveform = "waveform";
const String OscillatorProcessor::Constants::Identifiers::Oscillator = "oscillator";

const String OscillatorProcessor::Constants::Names::Semi = "Semi";
const String OscillatorProcessor::Constants::Names::Cents = "Cents";
const String OscillatorProcessor::Constants::Names::Gain = "Gain";
const String OscillatorProcessor::Constants::Names::Waveform = "Waveform";
const String OscillatorProcessor::Constants::Names::Oscillator = "Oscillator";

OscillatorProcessor::OscillatorProcessor(int ID,
                                         ModulationMatrix* modulationMatrix,
                                         AudioProcessorValueTreeState& audioProcessorValueTreeState,
                                         IDManager& idManager,
                                         int bufferSize,
                                         int sampleRate,
                                         std::vector<Wavetable*>& wavetables) :
Processor(ID,
          modulationMatrix,
          audioProcessorValueTreeState,
          idManager,
          bufferSize),
sampleRate(sampleRate), wavetables(wavetables)
{
    audioProcessorValueTreeState.createAndAddParameter(semiParameterStringID(),
                                                       Constants::Names::Semi,
                                                       String(),
                                                       NormalisableRange<float>(-36.0f, 36.0f, 1.0f),
                                                       0.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(centsParameterStringID(),
                                                       Constants::Names::Cents,
                                                       String(),
                                                       NormalisableRange<float>(-100.0f, 100.0f, 1.0f),
                                                       0.0f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(gainParameterStringID(),
                                                       Constants::Names::Gain,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.8f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(waveformParameterStringID(),
                                                       Constants::Names::Waveform,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 3.0f, 1.0f),
                                                       0.0f,
                                                       nullptr,
                                                       nullptr);
    
    gainParameterID = idManager.getNewID();
    semiParameterID = idManager.getNewID();
    centsParameterID = idManager.getNewID();
    waveformParameterID = idManager.getNewID();
    
    calculateFrqRad();
}

String OscillatorProcessor::semiParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Semi;
}

String OscillatorProcessor::centsParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Cents;
}

String OscillatorProcessor::gainParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Gain;
}

String OscillatorProcessor::waveformParameterStringID() const
{
    return stringIdentifier() + "_" + Constants::Identifiers::Waveform;
}

String OscillatorProcessor::stringIdentifier() const
{
    return Constants::Identifiers::Oscillator + String(ID);
}

String OscillatorProcessor::name() const
{
    return Constants::Names::Oscillator;
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
    if (hasProcessed) return;
    
    Range<float> semiRange = audioProcessorValueTreeState.getParameterRange(Constants::Identifiers::Semi).getRange();
    
    float semiModulation = semiRange.getEnd() * modulationMatrix->getValueForDestinationID(semiParameterID);
    int oscNote = currentNote + *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Semi);
    
    Range<float> centsRange = audioProcessorValueTreeState.getParameterRange(Constants::Identifiers::Cents).getRange();
    float centsModulation = centsRange.getEnd() * modulationMatrix->getValueForDestinationID(centsParameterID);
    
    // Assumes wavetableIndex is within range of wavetables for speed
    const int wavetableIndex = (const int)*audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Waveform);
    Wavetable* wavetable = wavetables[wavetableIndex];
    
    float cents = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Cents);
    frequency = getFrequencyFromFloatNote(oscNote + semiModulation + (cents + centsModulation)/100.0);
    calculatePhaseIncrement();
    
    if (phaseIncrement != 0.0 && currentNote >= 0)
    {
        float* subtable = wavetable->getSubtableForFrequency(frequency);
        int tableSize = wavetable->getTableSize();
        
        float gain = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Gain);
        const float gainModulation = modulationMatrix->getValueForDestinationID(gainParameterID);
        const float newKnobValue = std::max(std::min(1.0f, gain + gainModulation), 0.0f);
        const float level = newKnobValue;
        
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
                    buffer.addSample(channel, sampleIdx, currentSample);
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
                // Interpolate for better accuracy
                float indexFractional = ((currentPhase / twoPi) * tableSize) - index;
                FloatType currentSample = level * (subtable[index] + ((subtable[(index + 1) % tableSize] - subtable[index]) * indexFractional));
                
                for (int channel = 0; channel < buffer.getNumChannels(); channel++)
                {
                    buffer.addSample(channel, sampleIdx, currentSample);
                }
                
                currentPhase += phaseIncrement;
                if (currentPhase >= twoPi)
                {
                    currentPhase -= twoPi;
                }
            }
        }
    }
    
    if (output != nullptr)
    {
        output->renderNextBlock(buffer, startSample, numSamples);
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
