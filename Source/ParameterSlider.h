/*
  ==============================================================================

    ParameterSlider.h
    Created: 6 Oct 2016 9:17:11pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef PARAMETERSLIDER_H_INCLUDED
#define PARAMETERSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class ParameterSlider : public Slider, public DragAndDropTarget,
private Timer
{
public:
    ParameterSlider(AudioProcessorParameter& p)
    : Slider(p.getName(256)), param(p)
    {
        setRange(0.0, 1.0, 0.0);
        startTimerHz(30);
        updateSliderPos();
    }
    
    void valueChanged() override
    {
        param.setValueNotifyingHost((float)Slider::getValue());
    }
    
    void timerCallback() override { updateSliderPos(); }
    
    void startedDragging() override { param.beginChangeGesture(); }
    void stoppedDragging() override { param.endChangeGesture(); }
    
    double getValueFromText(const String& text) override { return param.getValueForText(text); }
    String getTextFromValue(double value) override { return param.getText((float)value, 1024); }
    
    void updateSliderPos()
    {
        const float newValue = param.getValue();
        
        if (newValue != (float)Slider::getValue() && !isMouseButtonDown())
            Slider::setValue(newValue);
    }
    
    virtual void itemDragEnter(const SourceDetails& dragSourceDetails) override
    {
        originalSliderFillColour = findColour(rotarySliderFillColourId);
        setColour(rotarySliderFillColourId, Colour(0, 200, 23));
    }
    
    virtual void itemDragExit(const SourceDetails& dragSourceDetails) override
    {
        setColour(rotarySliderFillColourId, originalSliderFillColour);
    }
    
    virtual bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override
    {
        return dragSourceDetails.description.equals(1) && (parameterType == ParameterTypeGain || parameterType == ParameterTypeFilterFrequency);
    }
    
    virtual void itemDropped(const SourceDetails& dragSourceDetails) override
    {
        setColour(rotarySliderFillColourId, originalSliderFillColour);
        ModulationParameter modParam;
        modParam.isModulated = true;
        modParam.modulatorId = static_cast<uint32>(int(dragSourceDetails.description));
        modulationMatrix->set(parameterType, modParam);
    }
    
    AudioProcessorParameter& param;
    ParameterType parameterType;
    HashMap<int, ModulationParameter>* modulationMatrix;
    
private:
    Colour originalSliderFillColour;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider)
    
};



#endif  // PARAMETERSLIDER_H_INCLUDED
