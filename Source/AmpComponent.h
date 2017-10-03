/*
  ==============================================================================

    AmpComponent.h
    Created: 6 Oct 2016 3:15:30pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef AMPCOMPONENT_H_INCLUDED
#define AMPCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterSlider.h"
#include "AmpParameterContainer.h"


//==============================================================================
/*
*/
class AmpComponent    : public Component
{
public:
    AmpComponent(AmpParameterContainer& parameterContainer);
    ~AmpComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpComponent)
    
    AmpParameterContainer& parameterContainer;
    
    ScopedPointer<ParameterSlider> gainKnob;
    Label gainLabel;
};


#endif  // AMPCOMPONENT_H_INCLUDED
