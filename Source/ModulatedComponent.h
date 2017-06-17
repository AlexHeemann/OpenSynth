/*
  ==============================================================================

    ModulatedComponent.h
    Created: 10 May 2017 1:26:18pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterSlider.h"
#include "ModulationPopover.h"
#include "Module.h"
#include "ModulationSink.h"

//==============================================================================
/*
*/
class ModulatedComponent    : public Component, public Module, public DragAndDropTarget
{
public:    
    ModulatedComponent(OpenSynthAudioProcessorEditor& editor, AudioProcessorParameter& p, int ID);
    ~ModulatedComponent();

    ParameterSlider* getSlider() const { return slider; }
    
    void paint (Graphics&) override;
    void resized() override;
    void update();
    
    void setHighlighted(bool highlighted)
    {
        isHighlighted = highlighted;
        slider->setHighlighted(highlighted);
        modulationSink->setHighlighted(highlighted);
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
        slider->setHighlighted(false);
        if (listener != nullptr)
        {
            listener->itemDropped(dragSourceDetails.description, ID);
        }
    }
    
    void setTextBoxStyle (const Slider::TextEntryBoxPosition newPosition, const bool isReadOnly,
                           const int textEntryBoxWidth, const int textEntryBoxHeight);
    
    void setListener(DragAndDropListener* listener) { this->listener = listener; }
    DragAndDropListener* getListener() { return listener; }
    
private:
    ScopedPointer<ParameterSlider> slider;
    ScopedPointer<ModulationSink> modulationSink;
    ScopedPointer<ModulationPopover> modulationPopover;
    
    Colour originalSliderFillColour;
    Colour originalSliderOutlineColour;
    Colour originalBackgroundColour;
    Colour originalTrackColour;
    bool isHighlighted = false;
    DragAndDropListener* listener;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatedComponent)
};
