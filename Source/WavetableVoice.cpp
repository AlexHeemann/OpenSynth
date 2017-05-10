/*
  ==============================================================================

    WavetableVoice.cpp
    Created: 6 Oct 2016 9:35:15am
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "WavetableVoice.h"
#include "OscillatorParameterContainer.h"
#include "FilterParameterContainer.h"

WavetableVoice::WavetableVoice(Wavetable* wavetable) : phaseIncrement1(0.0), phaseIncrement2(0.0), osc1Wavetable(wavetable), osc2Wavetable(wavetable)
{
    filterProcessor = new FilterProcessor(modulationMatrix);
    ampProcessor = new AmpProcessor(modulationMatrix);
}

WavetableVoice::~WavetableVoice()
{
    delete ampEnvelopeGenerator;
    delete filterEnvelopeGenerator;
}

void WavetableVoice::setAmpEnvelopeGenerator(EnvelopeGenerator* ampEnvelopeGenerator)
{
    this->ampEnvelopeGenerator = ampEnvelopeGenerator;
    setupEnvelope(ampEnvelopeGenerator);
    ampProcessor->setEnvelopeGenerator(ampEnvelopeGenerator);
}

void WavetableVoice::setFilterEnvelopeGenerator(EnvelopeGenerator *filterEnvelopeGenerator)
{
    this->filterEnvelopeGenerator = filterEnvelopeGenerator;
    setupEnvelope(filterEnvelopeGenerator);
    filterProcessor->setEnvelopeGenerator(filterEnvelopeGenerator);
}

void WavetableVoice::setupEnvelope(EnvelopeGenerator* envelopeGenerator)
{
    envelopeGenerator->setSampleRate(getSampleRate());
    envelopeGenerator->resetEnvelope();
}

void WavetableVoice::setOsc1Wavetable(Wavetable* wavetable)
{
    this->osc1Wavetable = wavetable;
}

void WavetableVoice::setOsc2Wavetable(Wavetable* wavetable)
{
    this->osc2Wavetable = wavetable;
}

void WavetableVoice::setOscillatorParameterContainer(OscillatorParameterContainer* oscillatorParameterContainer)
{
    this->oscillatorParameterContainer = oscillatorParameterContainer;
}

void WavetableVoice::setFilterParameterContainer(FilterParameterContainer* filterParameterContainer)
{
    this->filterParameterContainer = filterParameterContainer;
}

void WavetableVoice::startNote(int midiNoteNumber, float velocity,
               SynthesiserSound* sound,
               int currentPitchWheelPosition)
{
    currentPhase1 = 0.0;
    currentPhase2 = 0.0;
    level = velocity * 0.15;
    releaseCounter = 0;
    
    frequency1 = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    frequency2 = frequency1;
    frqRad = (2.0 * double_Pi) / getSampleRate();
    
    calculatePhaseIncrement();
    
    resetEnvelope(ampEnvelopeGenerator);
    resetEnvelope(filterEnvelopeGenerator);
    resetEnvelope(envelopeGenerator1);
    resetEnvelope(envelopeGenerator2);
    filterProcessor->resetFilter();
}

void WavetableVoice::resetEnvelope(EnvelopeGenerator* envelopeGenerator)
{
    if (envelopeGenerator != nullptr)
    {
        envelopeGenerator->resetEnvelope();
    }
}

void WavetableVoice::calculatePhaseIncrement()
{
    phaseIncrement1 = frqRad * frequency1;
    phaseIncrement2 = frqRad * frequency2;
}

void WavetableVoice::stopNote(float velocity, bool allowTailOff)
{
    if (allowTailOff && ampEnvelopeGenerator != nullptr && ampEnvelopeGenerator->getReleaseRate() > 0)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.
        
        // we only need to begin a tail-off if it's not already doing so - the
        // stopNote method could be called more than once.
        if (releaseCounter == 0)
        {
            releaseCounter = ampEnvelopeGenerator->getReleaseRate() * getSampleRate();
            ampEnvelopeGenerator->setEnvelopeState(EnvelopeGenerator::EnvelopeStateRelease);
            filterEnvelopeGenerator->setEnvelopeState(EnvelopeGenerator::EnvelopeStateRelease);
        }
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..
        clearCurrentNote();
        phaseIncrement1 = 0.0;
        currentPhase1 = 0.0;
        phaseIncrement2 = 0.0;
        currentPhase2 = 0.0;
    }
}

double getFrequencyFromFloatNote(float note)
{
    double frequencyOfA = 440.0;
    return frequencyOfA * powf (2.0, (note - 69) / 12.0);
}

template <typename FloatType>
void WavetableVoice::processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples)
{
    modulationMatrix->clear();
    
    ampEnvelopeGenerator->calculateEnvelopeBuffer(numSamples);
    filterEnvelopeGenerator->calculateEnvelopeBuffer(numSamples);
    envelopeGenerator1->calculateEnvelopeBuffer(numSamples);
    envelopeGenerator2->calculateEnvelopeBuffer(numSamples);
    lfo1->oscillate(numSamples);
    
    modulationMatrix->process();
    
    // This buffer is used to calculate all the samples for this voice, it then gets added to the overall output buffer of the synth
    AudioBuffer<FloatType> localBuffer = AudioBuffer<FloatType>(outputBuffer.getNumChannels(), outputBuffer.getNumSamples());
    localBuffer.clear();
    float localOscMix = oscillatorParameterContainer->getOscMixParameter()->get();
 
    int currentNote = getCurrentlyPlayingNote();
    if (currentNote >= 0)
    {
        Range<int> osc1ModRange = oscillatorParameterContainer->getOsc1SemiParameter()->getRange();
        float osc1SemiModulation = osc1ModRange.getEnd() * modulationMatrix->getValueForDestinationID(ParameterIDOscillator1Semi);
        Range<int> osc2ModRange = oscillatorParameterContainer->getOsc2SemiParameter()->getRange();
        float osc2SemiModulation = osc2ModRange.getEnd() * modulationMatrix->getValueForDestinationID(ParameterIDOscillator2Semi);
        int osc1Note = currentNote + oscillatorParameterContainer->getOsc1SemiParameter()->get();
        int osc2Note = currentNote + oscillatorParameterContainer->getOsc2SemiParameter()->get();
        
        Range<int> osc1CentsModRange = oscillatorParameterContainer->getOsc1Cents()->getRange();
        float osc1CentsModulation = osc1CentsModRange.getEnd() * modulationMatrix->getValueForDestinationID(ParameterIDOscillator1Cents);
        Range<int> osc2CentsModRange = oscillatorParameterContainer->getOsc2Cents()->getRange();
        float osc2CentsModulation = osc2CentsModRange.getEnd() * modulationMatrix->getValueForDestinationID(ParameterIDOscillator1Cents);
        
        frequency1 = getFrequencyFromFloatNote(osc1Note + osc1SemiModulation + (oscillatorParameterContainer->getOsc1Cents()->get()/100.0));
        frequency2 = getFrequencyFromFloatNote(osc2Note + osc2SemiModulation + (oscillatorParameterContainer->getOsc2Cents()->get()/100.0));
        
        calculatePhaseIncrement();
    }
    
    if (phaseIncrement1 != 0.0 && phaseIncrement2 != 0.0)
    {
        float* subtable1 = osc1Wavetable->getSubtableForFrequency(frequency1);
        int tableSize1 = osc1Wavetable->getTableSize();
        
        float* subtable2 = osc2Wavetable->getSubtableForFrequency(frequency2);
        int tableSize2 = osc2Wavetable->getTableSize();
        
        double twoPi = 2.0 * double_Pi;
        if (releaseCounter > 0)
        {
            for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
            {
                int index1 = (int)((currentPhase1 / twoPi) * tableSize1);
                // Interpolate for better accuracy
                float index1Fractional = ((currentPhase1 / twoPi) * tableSize1) - index1;
                FloatType currentSample1 = level * (subtable1[index1] + ((subtable1[(index1 + 1) % tableSize1] - subtable1[index1]) * index1Fractional)) * (1 - localOscMix);
                
                int index2 = (int)((currentPhase2 / twoPi) * tableSize2);
                float index2Fractional = ((currentPhase2 / twoPi) * tableSize2) - index2;
                FloatType currentSample2 = level * (subtable2[index2] + ((subtable2[(index2 + 1) % tableSize2] - subtable2[index2]) * index2Fractional)) * localOscMix;
                
                for (int channel = 0; channel < localBuffer.getNumChannels(); channel++)
                {
                    localBuffer.setSample(channel, sampleIdx, currentSample1 + currentSample2);
                }
                
                currentPhase1 += phaseIncrement1;
                if (currentPhase1 >= twoPi)
                {
                    currentPhase1 -= twoPi;
                }
                currentPhase2 += phaseIncrement2;
                if (currentPhase2 >= twoPi)
                {
                    currentPhase2 -= twoPi;
                }
                releaseCounter--;
                
                if (releaseCounter <= 0)
                {
                    clearCurrentNote();
                    phaseIncrement1 = 0.0;
                    currentPhase1 = 0.0;
                    phaseIncrement2 = 0.0;
                    currentPhase2 = 0.0;
                    break;
                }
            }
        }
        else
        {
            for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
            {
                int index1 = (int)((currentPhase1 / twoPi) * tableSize1);
                FloatType currentSample1 = level * subtable1[index1] * (1 - localOscMix);
                
                int index2 = (int)((currentPhase2 / twoPi) * tableSize2);
                FloatType currentSample2 = level * subtable2[index2] * localOscMix;
                
                for (int channel = 0; channel < localBuffer.getNumChannels(); channel++)
                {
                    localBuffer.setSample(channel, sampleIdx, currentSample1 + currentSample2);
                }
                
                currentPhase1 += phaseIncrement1;
                if (currentPhase1 >= twoPi)
                {
                    currentPhase1 -= twoPi;
                }
                currentPhase2 += phaseIncrement2;
                if (currentPhase2 >= twoPi)
                {
                    currentPhase2 -= twoPi;
                }
            }
        }
    }
    
    filterProcessor->renderNextBlock(localBuffer, startSample, numSamples);
    ampProcessor->renderNextBlock(localBuffer, startSample, numSamples);
    
    // Add samples from this voice to the output buffer
    for (int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++)
    {
        for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample + sampleIdx, localBuffer.getSample(channel, sampleIdx));
        }
    }
}
