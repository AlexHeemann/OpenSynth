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

class ModulationMatrix;

class Module
{
public:
    Module(int ID, AudioProcessor& processor) : ID(ID) {};
    ~Module() {};
    
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
    
protected:
    int ID;
    ModulationMatrix* modulationMatrix;
};



#endif  // MODULE_H_INCLUDED
