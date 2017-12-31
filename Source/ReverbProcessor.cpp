/*
  ==============================================================================

    ReverbProcessor.cpp
    Created: 24 Nov 2016 8:05:38pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "ReverbProcessor.h"
#include "ReverbParameterContainer.h"
#include "ModulationMatrix.h"

const String ReverbProcessor::Constants::Identifiers::Reverb = "reverb";
const String ReverbProcessor::Constants::Identifiers::Size = "size";
const String ReverbProcessor::Constants::Identifiers::Damping = "damping";
const String ReverbProcessor::Constants::Identifiers::DryLevel = "dry_level";
const String ReverbProcessor::Constants::Identifiers::WetLevel = "wet_level";
const String ReverbProcessor::Constants::Identifiers::Width = "width";

const String ReverbProcessor::Constants::Names::Reverb = "Reverb";
const String ReverbProcessor::Constants::Names::Size = "Size";
const String ReverbProcessor::Constants::Names::Damping = "Damping";
const String ReverbProcessor::Constants::Names::DryLevel = "Dry";
const String ReverbProcessor::Constants::Names::WetLevel = "Wet";
const String ReverbProcessor::Constants::Names::Width = "Width";

ReverbProcessor::ReverbProcessor(int ID,
                                 ModulationMatrix* modulationMatrix,
                                 AudioProcessorValueTreeState& audioProcessorValueTreeState,
                                 IDManager& idManager,
                                 int bufferSize,
                                 int sampleRate) :
Processor(ID,
          modulationMatrix,
          audioProcessorValueTreeState,
          idManager,
          bufferSize)
{
    reverbSizeParameterID = idManager.getNewID();
    reverbDampingParameterID = idManager.getNewID();
    reverbWetLevelParameterID = idManager.getNewID();
    reverbDryLevelParameterID = idManager.getNewID();
    reverbWidthParameterID = idManager.getNewID();
    
    audioProcessorValueTreeState.createAndAddParameter(reverbSizeParameterStringID(),
                                                       Constants::Names::Size,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.5f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(reverbDampingParameterStringID(),
                                                       Constants::Names::Damping,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.5f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(reverbDryLevelParameterStringID(),
                                                       Constants::Names::DryLevel,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.4f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(reverbWetLevelParameterStringID(),
                                                       Constants::Names::WetLevel,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.33f,
                                                       nullptr,
                                                       nullptr);
    
    audioProcessorValueTreeState.createAndAddParameter(reverbWidthParameterStringID(),
                                                       Constants::Names::Width,
                                                       String(),
                                                       NormalisableRange<float>(0.0f, 1.0f),
                                                       0.2f,
                                                       nullptr,
                                                       nullptr);
}

String ReverbProcessor::stringIdentifier() const
{
    return ReverbProcessor::Constants::Identifiers::Reverb + String(ID);
}

String ReverbProcessor::reverbSizeParameterStringID() const
{
    return stringIdentifier() + "_" + ReverbProcessor::Constants::Names::Size;
}

String ReverbProcessor::reverbDampingParameterStringID() const
{
    return stringIdentifier() + "_" + ReverbProcessor::Constants::Names::Damping;
}

String ReverbProcessor::reverbWetLevelParameterStringID() const
{
    return stringIdentifier() + "_" + ReverbProcessor::Constants::Names::WetLevel;
}

String ReverbProcessor::reverbDryLevelParameterStringID() const
{
    return stringIdentifier() + "_" + ReverbProcessor::Constants::Names::DryLevel;
}

String ReverbProcessor::reverbWidthParameterStringID() const
{
    return stringIdentifier() + "_" + ReverbProcessor::Constants::Names::Width;
}

template <typename FloatType>
void ReverbProcessor::processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples)
{
    ReverbDouble::Parameters parameters;
    parameters.roomSize = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Size);
    parameters.damping = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Damping);
    parameters.dryLevel = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::DryLevel);
    parameters.wetLevel = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::WetLevel);
    parameters.width = *audioProcessorValueTreeState.getRawParameterValue(Constants::Identifiers::Width);
    
    reverb.setParameters(parameters);
    
    if (buffer.getNumChannels() >= 2)
    {
        reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), numSamples);
    }
    else
    {
        reverb.processMono(buffer.getWritePointer(0), numSamples);
    }
    
    if (output != nullptr)
    {
        output->renderNextBlock(buffer, startSample, numSamples);
    }
}

void ReverbProcessor::setSampleRate(const int sampleRate)
{
    this->sampleRate = sampleRate;
    reverb.setSampleRate(sampleRate);
}

void ReverbProcessor::reset()
{
    reverb.reset();
}
