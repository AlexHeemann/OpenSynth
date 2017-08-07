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
    typedef enum {
        HighPass = 1,
        LowPass = 2,
        BandPass = 3,
        AllPass = 4
    } FilterType;
    
    FilterProcessor(ModulationMatrix* modulationMatrix, int bufferSize);
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
    
    void resetFilter();
    void setActiveFilter(FilterType activeFilter);
    void setParameterContainer(FilterParameterContainer* parameterContainer);    
    
private:
    template <typename FloatType>
    void processBuffer(AudioBuffer<FloatType>& buffer, int startSample, int numSamples);
    template <typename FloatType, typename DspFilterType>
    void processBufferWithFilter(AudioBuffer<FloatType> &buffer, int startSample, int numSamples, std::vector<DspFilterType>& filters);
    void initialiseLowPassFilter(double frequency);
    void initialiseHighPassFilter(double frequency);
    void initialiseBandPassFilter(double frequency);
    void initialiseAllPassFilter(double frequency);
    
    // Contains filters for left and right channel
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::LowPass, 1>> lowPassFilters;
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::HighPass, 1>> highPassFilters;
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::BandPass1, 1>> bandPassFilters;
    std::vector<Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::AllPass, 1>> allPassFilters;
    
    template <typename DspFilterType>
    std::vector<DspFilterType>& getActiveFilter();
    
    FilterType activeFilter;
    FilterParameterContainer* parameterContainer;    
};


#endif  // FILTERPROCESSOR_H_INCLUDED
