/*
  ==============================================================================

    ReverbProcessor.h
    Created: 24 Nov 2016 8:05:38pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef REVERBPROCESSOR_H_INCLUDED
#define REVERBPROCESSOR_H_INCLUDED

#include "Processor.h"
#include "ReverbDouble.h"

class ReverbParameterContainer;

class ReverbProcessor : public Processor
{
public:
    
    struct Constants
    {
        struct Identifiers
        {
            static const String Reverb;
            static const String Size;
            static const String Damping;
            static const String DryLevel;
            static const String WetLevel;
            static const String Width;
        };
        struct Names
        {
            static const String Reverb;
            static const String Size;
            static const String Damping;
            static const String DryLevel;
            static const String WetLevel;
            static const String Width;
        };
    };
    
    ReverbProcessor(int ID,
                    ModulationMatrix* modulationMatrix,
                    AudioProcessorValueTreeState& audioProcessorValueTreeState,
                    IDManager& idManager,
                    int bufferSize,
                    int sampleRate);
    virtual ~ReverbProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    
    void setSampleRate(const int sampleRate) override;
    const int getSampleRate() const { return sampleRate; };
    void reset() override;
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
    
    int sampleRate = 0;
    
    int reverbSizeParameterID;
    int reverbDampingParameterID;
    int reverbWetLevelParameterID;
    int reverbDryLevelParameterID;
    int reverbWidthParameterID;
    
    String stringIdentifier() const override;
    String reverbSizeParameterStringID() const;
    String reverbDampingParameterStringID() const;
    String reverbWetLevelParameterStringID() const;
    String reverbDryLevelParameterStringID() const;
    String reverbWidthParameterStringID() const;
    
    ReverbDouble reverb;
    ReverbDouble::Parameters reverbParameters;
};

#endif  // REVERBPROCESSOR_H_INCLUDED
