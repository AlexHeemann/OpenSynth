/*
  ==============================================================================

    ModulationOverview.h
    Created: 10 May 2017 8:51:55pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ModulationPopover.h"
#include "PluginProcessor.h"

class OpenSynthAudioProcessor;
class ModulationMatrix;

//==============================================================================
/*
*/
class ModulationOverview    : public Component, public ModulationPopover::Listener
{
public:
    ModulationOverview(int destinationID, OpenSynthAudioProcessor& processor);
    ~ModulationOverview();

    void paint (Graphics&) override;
    void resized() override;
    void update();
    
    // ModulationPopover::Listener
    void modulationPopoverValueChanged(ModulationPopover* modulationPopover) override;

private:
    int destinationID;
    OpenSynthAudioProcessor& processor;
    std::vector<std::unique_ptr<ModulationPopover>> modulationPopovers;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationOverview)
};
