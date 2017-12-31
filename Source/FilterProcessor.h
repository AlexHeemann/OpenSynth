/*
  ==============================================================================

    FilterProcessor.h
    Created: 8 Oct 2016 2:44:22pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef FILTERPROCESSOR_H_INCLUDED
#define FILTERPROCESSOR_H_INCLUDED

#include "Processor.h"
#include "DspFilters/Dsp.h"

class FilterParameterContainer;
class ModulationMatrix;

class FilterProcessor : public Processor
{
public:
    
    struct Constants
    {
        struct Identifiers
        {
            static const String Filter;
            
            static const String Frequency;
            static const String Resonance;
            static const String FilterType;
        };
        
        struct Names
        {
            static const String Filter;
            
            static const String Frequency;
            static const String Resonance;
            static const String FilterType;
        };
    };
    
    FilterProcessor(int ID,
                    ModulationMatrix* modulationMatrix,
                    AudioProcessorValueTreeState& audioProcessorValueTreeState,
                    IDManager& idManager,
                    int bufferSize);
    virtual ~FilterProcessor() {};
    
    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
    {
        processBuffer(outputBuffer, startSample, numSamples);
    }
    void renderNextBlock() override;
    
    void reset() override;
    String name() const override;
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
    template <typename FloatType, typename DspFilterType>
    void processBufferWithFilter(AudioBuffer<FloatType> &buffer, int startSample, int numSamples, std::vector<DspFilterType>& filters);
    void initialiseLowPassFilter(double frequency);
    void initialiseHighPassFilter(double frequency);
    void initialiseBandPassFilter(double frequency);
    void initialiseAllPassFilter(double frequency);
    
    int filterFrequencyParameterID;
    int filterResonanceParameterID;
    
    String stringIdentifier() const override;
    
    String filterFrequencyParameterStringID() const;
    String filterResonanceParameterStringID() const;
    String filterTypeParameterStringID() const;
    
    // Contains filters for left and right channel
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::LowPass, 1>> lowPassFilters;
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::HighPass, 1>> highPassFilters;
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::BandPass1, 1>> bandPassFilters;
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::AllPass, 1>> allPassFilters;
    
    template <typename DspFilterType>
    std::vector<DspFilterType>& getActiveFilter();
};


#endif  // FILTERPROCESSOR_H_INCLUDED
