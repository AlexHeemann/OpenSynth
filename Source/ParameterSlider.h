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
#include "Module.h"
#include "DragAndDropListener.h"

class ParameterSlider : public Module, public Slider, public DragAndDropTarget,
private Timer
{
public:
    ParameterSlider(AudioProcessorParameter& p, int ID) : Module(ID), Slider(p.getName(256)), param(p)
    {
        setRange(0.0, 1.0, 0.0);
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
    
    void setHighlighted(bool highlighted)
    {
        if (highlighted && !isHighlighted)
        {
            isHighlighted = true;
            originalSliderFillColour = findColour(rotarySliderFillColourId);
            originalSliderOutlineColour = findColour(rotarySliderOutlineColourId);
            originalBackgroundColour = findColour(backgroundColourId);
            originalTrackColour = findColour(trackColourId);
            setColour(rotarySliderOutlineColourId, Colour(0, 200, 23));
            setColour(rotarySliderFillColourId, Colour(0, 200, 23));
            setColour(backgroundColourId, Colour(0, 200, 23));
            setColour(trackColourId, Colour(0, 200, 23));
        }
        else if (!highlighted)
        {
            isHighlighted = false;
            setColour(rotarySliderOutlineColourId, originalSliderOutlineColour);
            setColour(rotarySliderFillColourId, originalSliderFillColour);
            setColour(backgroundColourId, originalBackgroundColour);
            setColour(trackColourId, originalTrackColour);
        }
    }
    
    virtual void itemDragEnter(const SourceDetails& dragSourceDetails) override
    {
        setHighlighted(true);
    }
    
    virtual void itemDragExit(const SourceDetails& dragSourceDetails) override
    {
        setHighlighted(false);
    }
    
    virtual bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override
    {
        return true;
    }
    
    virtual void itemDropped(const SourceDetails& dragSourceDetails) override
    {
        setHighlighted(false);
        if (listener != nullptr)
        {
            listener->itemDropped(dragSourceDetails.description, ID);
        }
    }
    
    void setListener(DragAndDropListener* listener) { this->listener = listener; }
    DragAndDropListener* getListener() { return listener; }
    
    AudioProcessorParameter& param;
    
private:
    Colour originalSliderFillColour;
    Colour originalSliderOutlineColour;
    Colour originalBackgroundColour;
    Colour originalTrackColour;
    bool isHighlighted = false;
    DragAndDropListener* listener;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider)
    
};



#endif  // PARAMETERSLIDER_H_INCLUDED
