/*
  ==============================================================================

    AmpProcessor.h
    Created: 6 Oct 2016 2:33:19pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef AMPPROCESSOR_H_INCLUDED
#define AMPPROCESSOR_H_INCLUDED

#include "Processor.h"

class AmpParameterContainer;

class AmpProcessor : public Processor
{
public:
    
    struct Constants
    {
        struct Identifiers
        {
            static const String Amp;
            static const String Gain;
        };
        struct Names
        {
            static const String Amp;
            static const String Gain;
        };
    };
    
    AmpProcessor(int ID,
                 ModulationMatrix* modulationMatrix, AudioProcessorValueTreeState& audioProcessorValueTreeState,
                 IDManager& idManager,
                 int bufferSize);
    virtual ~AmpProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock() override {};
    void reset() override {};
    
    String name() const override;
    
private:
    
    int gainParameterID;
    String gainParameterStringID() const;
    String stringIdentifier() const override;
    
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
};



#endif  // AMPPROCESSOR_H_INCLUDED
