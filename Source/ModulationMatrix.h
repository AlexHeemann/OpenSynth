/*
  ==============================================================================

    ModulationMatrix.h
    Created: 25 Apr 2017 12:19:50pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#ifndef MODULATIONMATRIX_H_INCLUDED
#define MODULATIONMATRIX_H_INCLUDED

#include "JuceHeader.h"
#include <unordered_map>
#include <list>
#include "ModulationMatrixData.h"

class ModulationMatrix
{
public:
    ModulationMatrix();
    ~ModulationMatrix() {};        
    
    void setValueForSourceID(int sourceID, double value)
    {
        sources[sourceID] = value;
    }
    
    void setValueForDestinationID(int destinationID, double value)
    {
        destinations[destinationID] = value;
    }
    
    double getValueForDestinationID(int destinationID)
    {
        return destinations[destinationID];
    }
    
    void updateModulationAmount(int sourceID, int destinationID, double modulationAmount)
    {
        data->updateModulationAmount(sourceID, destinationID, modulationAmount);
    }
    
    void addRow(int sourceID, int destinationID, double modulationAmount)
    {
        data->addRow(sourceID, destinationID, modulationAmount);
    }
    
    void addRow(int sourceID, int destinationID)
    {
        addRow(sourceID, destinationID, 1.0);
    }
    
    void removeRow(int sourceID, int destinationID)
    {
        data->removeRow(sourceID, destinationID);
    }
    
    std::unordered_map<int, std::unique_ptr<std::list<int>>>& getDestinationToModMap()
    {
        return data->getDestinationToModMap();
    }
    
    std::list<int>* getSourcesForDestination(int destinationID)
    {
        return data->getSourcesForDestination(destinationID);
    }
    
    void setData(ModulationMatrixData* data)
    {
        this->data = data;
    }
    
    ModulationMatrixData* getData() const
    {
        return data;
    }
    
    void process();
    void clear();
    
private:
    std::unordered_map<int, double> sources;
    std::unordered_map<int, double> destinations;
    ModulationMatrixData* data;
};



#endif  // MODULATIONMATRIX_H_INCLUDED
