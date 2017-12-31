/*
  ==============================================================================

    Module.h
    Created: 25 Apr 2017 2:00:10pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#include "JuceHeader.h"
#include "IDManager.h"

class ModulationMatrix;

class Module
{
public:
    Module(int ID,
           ModulationMatrix *modulationMatrix,
           AudioProcessorValueTreeState& audioProcessorValueTreeState,
           IDManager& idManager) :
    ID(ID),
    modulationMatrix(modulationMatrix),
    audioProcessorValueTreeState(audioProcessorValueTreeState),
    idManager(idManager) {};
    
    virtual ~Module() {};
    
    int getID() { return ID; };
    void setID(int ID) { this-> ID = ID; };
    void setModulationMatrix(ModulationMatrix* modulationMatrix)
    {
        this->modulationMatrix = modulationMatrix;
    }
    
    ModulationMatrix* getModulationMatrix()
    {
        return modulationMatrix;
    }
    
    virtual void calculateModulation(int numSamples) = 0;
    virtual void reset() = 0;
    virtual void setSampleRate(int sampleRate) = 0;
    
    void writeModulationValue();
    
protected:
    int ID;
    double currentValue = 0.0;
    ModulationMatrix* modulationMatrix;
    AudioProcessorValueTreeState& audioProcessorValueTreeState;
    IDManager& idManager;
    
    virtual String stringIdentifier() const = 0;
};



#endif  // MODULE_H_INCLUDED
