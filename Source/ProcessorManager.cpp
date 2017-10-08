/*
  ==============================================================================

    ProcessorManager.cpp
    Created: 7 Aug 2017 1:52:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "ProcessorManager.h"
#include "Processor.h"
#include "OscillatorProcessor.h"
#include "AmpProcessor.h"

void ProcessorManager::renderNextBlock(AudioBuffer<float>& outputBuffer,
                                       int startSample,
                                       int numSamples)
{
    if (startOscillator != nullptr)
    {
        startOscillator->renderNextBlock(outputBuffer, startSample, numSamples);
    }
}

void ProcessorManager::renderNextBlock(AudioBuffer<double>& outputBuffer,
                                       int startSample,
                                       int numSamples)
{
    if (startOscillator != nullptr)
    {
        startOscillator->renderNextBlock(outputBuffer, startSample, numSamples);
    }
}

void ProcessorManager::removeProcessor(int processorID)
{
    if (processors.find(processorID) != processors.end())
    {
        processors.erase(processorID);
    }
}

void ProcessorManager::removeOscillator(int oscillatorID)
{
    if (oscillators.find(oscillatorID) != oscillators.end())
    {
        oscillators.erase(oscillatorID);
    }
}

void ProcessorManager::addOscillator(std::shared_ptr<OscillatorProcessor> oscillator)
{
    addProcessor(oscillator);
    oscillators[oscillator->getID()] = oscillator;
}

void ProcessorManager::addProcessor(std::shared_ptr<Processor> processor)
{
    processors[processor->getID()] = processor;
}

void ProcessorManager::connectSerial(int sourceID, int destinationID)
{
    if (processors.find(sourceID) != processors.end() && processors.find(destinationID) != processors.end())
    {
        processors[sourceID]->setOutput(processors[destinationID].get());
    }
}

void ProcessorManager::connect(int sourceID, int destinationID)
{
    if (processors.find(sourceID) != processors.end() && processors.find(destinationID) != processors.end())
    {
        processors[sourceID]->addOutput(processors[destinationID].get());
        processors[destinationID]->addInput(processors[sourceID].get());
    }
}

void ProcessorManager::disconnect(int sourceID, int destinationID)
{
    if (processors.find(sourceID) != processors.end() && processors.find(destinationID) != processors.end())
    {
        processors[sourceID]->removeOutput(processors[destinationID].get());
        processors[destinationID]->removeInput(processors[sourceID].get());
    }
}

void ProcessorManager::setNoteForOscillators(int note)
{
    for (auto oscillator : oscillators)
    {
        oscillator.second->setNote(note);
    }
}

void ProcessorManager::setAmpProcessor(std::shared_ptr<AmpProcessor> ampProcessor)
{
    if (this->ampProcessor != nullptr)
    {
        removeProcessor(this->ampProcessor->getID());
    }
    addProcessor(ampProcessor);
    this->ampProcessor = ampProcessor;
}

void ProcessorManager::resetOscillators()
{
    for (auto oscillator : oscillators)
    {
        oscillator.second->reset();
    }
}

void ProcessorManager::resetProcessors()
{
    for (auto processor : processors)
    {
        processor.second->reset();
    }
}

void ProcessorManager::setSampleRateForOscillators(int sampleRate)
{
    for (auto oscillator : oscillators)
    {
        oscillator.second->setSampleRate(sampleRate);
    }
}
