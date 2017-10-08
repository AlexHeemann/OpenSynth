/*
  ==============================================================================

    Processor.h
    Created: 6 Oct 2016 2:34:51pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <set>

class ModulationMatrix;

class Processor
{
public:
    Processor(ModulationMatrix *modulationMatrix, int bufferSize) :
    modulationMatrix(modulationMatrix),
    audioBuffer(AudioBuffer<float>(2, bufferSize))
    {
        audioBuffer.clear();
    };
    virtual ~Processor() {};
    
    virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) = 0;
    virtual void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) = 0;
    virtual void renderNextBlock() = 0;
    virtual void reset() = 0;
    
    void setModulationMatrix(ModulationMatrix* modulationMatrix) { this->modulationMatrix = modulationMatrix; }
    ModulationMatrix* getModulationMatrix() { return modulationMatrix; }
    
    AudioBuffer<float>& getAudioBuffer() { return audioBuffer; }
    
    void addInput(Processor* processor)
    {
        inputs.insert(processor);
    }
    void removeInput(Processor* processor)
    {
        inputs.erase(processor);
    }
    
    void addOutput(Processor* processor)
    {
        outputs.insert(processor);
    }
    void removeOutput(Processor* processor)
    {
        outputs.erase(processor);
    }
    
    void setOutput(Processor* processor) { this->output = processor; }
    Processor* getOutput() const { return this->output; }
    
    void prepare(int bufferSize)
    {
        if (audioBuffer.getNumSamples() != bufferSize)
        {
            audioBuffer.setSize(2, bufferSize);
        }
        hasProcessed = false;
    }
    
    std::set<Processor*>& getInputs() { return inputs; }
    std::set<Processor*>& getOutputs() { return outputs; }
    void setID(int ID) { this->ID = ID; }
    int getID() const { return ID; }
    
    void setBufferSize(int bufferSize)
    {
        audioBuffer.setSize(2, bufferSize);
    }
    
protected:
    int ID;
    bool hasProcessed = false;
    ModulationMatrix* modulationMatrix;
    AudioBuffer<float> audioBuffer;
    std::set<Processor*> inputs;
    std::set<Processor*> outputs;
    std::set<Processor*> dependants;
    int feedbackCounter = 0;
    
    Processor* output;
    
    // For parallel processing
    template <typename FloatType>
    void aggregateInputs(AudioBuffer<FloatType>& buffer)
    {
        std::set<Processor*> nextDependants = dependants;
        nextDependants.insert(this);
        
        for (auto input : inputs)
        {
            input->renderNextBlock();
            AudioBuffer<float> inputBuffer = input->getAudioBuffer();
            for (int channel = 0; channel < inputBuffer.getNumChannels(); ++channel)
            {
                for (int sample = 0; sample < inputBuffer.getNumSamples(); ++sample)
                {
                    const float* const inputChannelData = inputBuffer.getReadPointer(channel);
                    FloatType* const outputChannelData = buffer.getWritePointer(channel);
                    outputChannelData[sample] += inputChannelData[sample];
                }
            }
        }
    }
};


#endif  // PROCESSOR_H_INCLUDED
