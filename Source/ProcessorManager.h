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
#include "Processor.h"

class ProcessorManager
{
public:
    ProcessorManager() {}
    ~ProcessorManager() {}
    
    void addProcessor(Processor* processor);
    
private:
    std::unordered_map<int, AudioBuffer<float>*> audioBuffers;
};
