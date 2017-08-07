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
    
    double getValueForSourceID(int sourceID)
    {
        return sources[sourceID];
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
    
    double getModulationAmount(int sourceID, int destinationID)
    {
        return data->getModulationAmount(sourceID, destinationID);
    }
    
    void connect(int sourceID, int destinationID)
    {
        data->connect(sourceID, destinationID);
    }
    
    void disconnect(int sourceID, int destinationID)
    {
        data->disconnect(sourceID, destinationID);
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
    
    void setSourceName(int source, std::string name)
    {
        data->setSourceName(source, name);
    }
    
    std::string& getSourceName(int source)
    {
        return data->getSourceName(source);
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
