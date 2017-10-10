/*
  ==============================================================================

    ModulationMatrix.cpp
    Created: 25 Apr 2017 12:19:50pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "ModulationMatrix.h"
#include "PluginProcessor.h"
#include "Module.h"
#include "EnvelopeGenerator.h"

ModulationMatrix::ModulationMatrix()
{
    destinations[ParameterIDFilterCutoff] = 0;
}

void ModulationMatrix::process()
{
    for (auto row : data->getRows())
    {
        destinations[row.destinationIndex] += sources[row.sourceIndex] * row.modulationAmount;
    }
}

void ModulationMatrix::clear()
{
    for (auto& source : sources)
    {
        source.second = 0;
    }
    for (auto& destination : destinations)
    {
        destination.second = 0;
    }
}

void ModulationMatrix::addModulator(std::shared_ptr<Module> modulator)
{
    modulator->setModulationMatrix(this);
    modulators[modulator->getID()] = modulator;
}

void ModulationMatrix::removeModulator(int modulatorID)
{
    if (modulators.find(modulatorID) != modulators.end())
    {
        modulators.erase(modulatorID);
    }
}

void ModulationMatrix::calculateModulation(int numSamples)
{
    for (auto modulator : modulators)
    {
        modulator.second->calculateModulation(numSamples);
    }
}

void ModulationMatrix::writeModulation()
{
    for (auto modulator : modulators)
    {
        modulator.second->writeModulationValue();
    }
}

void ModulationMatrix::addLFO(std::shared_ptr<LFO> lfo)
{
    addModulator(lfo);
    lfos[lfo->getID()] = lfo;
}

void ModulationMatrix::addEnvelope(std::shared_ptr<EnvelopeGenerator> envelope)
{
    addModulator(envelope);
    envelopes[envelope->getID()] = envelope;
}

void ModulationMatrix::removeLFO(int lfoID)
{
    removeModulator(lfoID);
    if (lfos.find(lfoID) != lfos.end())
    {
        lfos.erase(lfoID);
    }
}

void ModulationMatrix::removeEnvelope(int envelopeID)
{
    removeModulator(envelopeID);
    if (envelopes.find(envelopeID) != envelopes.end())
    {
        envelopes.erase(envelopeID);
    }
}

void ModulationMatrix::resetModulators()
{
    for (auto modulator : modulators)
    {
        modulator.second->reset();
    }
}

void ModulationMatrix::setSampleRateForModulators(int sampleRate)
{
    for (auto modulator : modulators)
    {
        modulator.second->setSampleRate(sampleRate);
    }
}

void ModulationMatrix::setEnvelopeState(EnvelopeState state)
{
    for (auto envelope : envelopes)
    {
        envelope.second->setEnvelopeState(state);
    }
}
