/*
  ==============================================================================

    DelayParameterContainer.h
    Created: 4 Dec 2016 7:36:30pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef DELAYPARAMETERCONTAINER_H_INCLUDED
#define DELAYPARAMETERCONTAINER_H_INCLUDED

#include "ParameterContainer.h"

class DelayParameterContainer: public ParameterContainer
{
public:
    DelayParameterContainer(int ID,
                            OpenSynth& openSynth,
                            OpenSynthAudioProcessor& processor) : ParameterContainer(ID,
                                                                                     synth,
                                                                                     processor)
    {
        delayTimeParameterID = synth.getIDManager().getNewID();
        delayFeedbackParameterID = synth.getIDManager().getNewID();
        delayMixParameterID = synth.getIDManager().getNewID();
        
        processor.addParameter(delayTime = new AudioParameterFloat("delayTime", "Delay Time", 0.0f, 1.0f, 0.5f));
        processor.addParameter(delayFeedback = new AudioParameterFloat("delayFeedback", "Delay Feedback", 0.0f, 1.0f, 0.5f));
        processor.addParameter(delaySpread = new AudioParameterFloat("delaySpread", "Delay Spread", 0.0f, 1.0f, 0.0f));
        processor.addParameter(delayMix = new AudioParameterFloat("delayMix", "Delay Mix", 0.0f, 1.0f, 0.0f));
        processor.addParameter(delayEnabled = new AudioParameterBool("delayEnabled", "Delay Enabled", false));
    }
    
    virtual ~DelayParameterContainer() {};
    
    int getDelayTimeParameterID() const { return delayTimeParameterID; }
    int getDelayFeedbackParameterID() const { return delayFeedbackParameterID; }
    int getDelayMixParameterID() const { return delayMixParameterID; }
    
    AudioParameterFloat* getDelayTimeParameter() const { return delayTime; };
    AudioParameterFloat* getDelayFeedbackParameter() const { return delayFeedback; };
    AudioParameterFloat* getDelaySpreadParameter() const { return delaySpread; };
    AudioParameterFloat* getDelayMixParameter() const { return delayMix; };
    AudioParameterBool* getDelayEnabledParameter() const { return delayEnabled; };
    
private:
    int delayTimeParameterID;
    int delayFeedbackParameterID;
    int delayMixParameterID;
    
    AudioParameterFloat* delayTime;
    AudioParameterFloat* delayFeedback;
    AudioParameterFloat* delaySpread;
    AudioParameterFloat* delayMix;
    AudioParameterBool* delayEnabled;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayParameterContainer);
};



#endif  // DELAYPARAMETERCONTAINER_H_INCLUDED
