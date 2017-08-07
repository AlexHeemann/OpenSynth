/*
  ==============================================================================

    OscillatorProcessor.cpp
    Created: 7 Aug 2017 6:58:17pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "OscillatorProcessor.h"

OscillatorProcessor::OscillatorProcessor(ModulationMatrix* modulationMatrix, int bufferSize) : Processor(modulationMatrix, bufferSize)
{
    
}

template <typename FloatType>
void OscillatorProcessor::processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples)
{
    
}
