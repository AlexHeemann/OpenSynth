/*
  ==============================================================================

    ProcessorManager.h
    Created: 7 Aug 2017 1:52:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include <unordered_map>
#include <list>
#include <memory>

class Processor;
class OscillatorProcessor;
class AmpProcessor;

class ProcessorManager
{
public:
    ProcessorManager() {}
    ~ProcessorManager() {}
    
    void addProcessor(std::shared_ptr<Processor> processor);
    void addOscillator(std::shared_ptr<OscillatorProcessor> oscillator);
    void setAmpProcessor(std::shared_ptr<AmpProcessor> ampProcessor);
    std::shared_ptr<AmpProcessor> getAmpProcessor() const { return ampProcessor; }
    
    void removeProcessor(int processorID);
    void removeOscillator(int oscillatorID);
    
    void connect(int sourceID, int destinationID);
    void disconnect(int sourceID, int destinationID);
    
    void setNoteForOscillators(int note);
    void resetOscillators();
    void resetProcessors();
    void setSampleRateForOscillators(int sampleRate);
    
    std::unordered_map<int, std::shared_ptr<Processor>>& getProcessors() { return processors; }
    std::unordered_map<int, std::shared_ptr<OscillatorProcessor>>& getOscillators() { return oscillators; }
    
private:
    std::shared_ptr<AmpProcessor> ampProcessor; // final output
    std::unordered_map<int, std::shared_ptr<Processor>> processors; // all processors
    std::unordered_map<int, std::shared_ptr<OscillatorProcessor>> oscillators; // only oscillators, a strict subset of `processors`
};
