/*
  ==============================================================================

    ModulationConnector.h
    Created: 19 Jun 2016 12:44:18pm
    Author:  Alex

  ==============================================================================
*/

#ifndef MODULATIONCONNECTOR_H_INCLUDED
#define MODULATIONCONNECTOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ModulationConnector    : public Component, MouseListener
{
public:
    ModulationConnector();
    ~ModulationConnector();

    void paint (Graphics&);
    void resized();

	uint32 getModulationId();
	void setModulationId(uint32 modulationId);

	virtual void mouseDown(const juce::MouseEvent & event);
	virtual void mouseDrag(const MouseEvent& event);

private:
	uint32 modulationId;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationConnector)
};


#endif  // MODULATIONCONNECTOR_H_INCLUDED
