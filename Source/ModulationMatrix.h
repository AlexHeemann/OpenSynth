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

struct ModulationMatrixRow
{
public:
    ModulationMatrixRow() {};
    ModulationMatrixRow(int sourceIndex,
                        int destinationIndex,
                        double modulationAmount) :
    sourceIndex(sourceIndex),
    destinationIndex(destinationIndex),
    modulationAmount(modulationAmount) {} ;
    ~ModulationMatrixRow() {};
    
    int sourceIndex;
    int destinationIndex;
    double modulationAmount;
    
private:
    
};

class ModulationMatrix
{
public:
    ModulationMatrix();
    ~ModulationMatrix() {};
    
    int keyFromIDs(int sourceID, int destinationID) const
    {
        return sourceID << 16 | destinationID;
    }
    
    int sourceIDFromKey(int key) const
    {
        return key >> 16;
    }
    
    int destinationIDFromKey(int key) const
    {
        return key & 0xFFFF;
    }
    
    void updateModulationAmount(int sourceID, int destinationID, double modulationAmount)
    {
        int index = mmRowsMap[keyFromIDs(sourceID, destinationID)];
        mmRows[index].modulationAmount = modulationAmount;
    }
    
    void addRow(int sourceID, int destinationID, double modulationAmount)
    {
        ModulationMatrixRow row = ModulationMatrixRow(sourceID, destinationID, modulationAmount);
        mmRows.push_back(row);
        mmRowsMap[keyFromIDs(sourceID, destinationID)] = mmRows.size() - 1;
    }
    
    void addRow(int sourceID, int destinationID)
    {
        addRow(sourceID, destinationID, 1.0);
    }
    
    void removeRow(int sourceID, int destinationID)
    {
        int key = keyFromIDs(sourceID, destinationID);
        if (mmRowsMap.find(key) == mmRowsMap.end())
        {
            return;
        }
        int index = mmRowsMap[key];
        mmRowsMap.erase(key);
        // Copy last element into removed spot and update index in map
        mmRows[index] = mmRows[mmRows.size() - 1];
        mmRowsMap[keyFromIDs(mmRows[index].sourceIndex, mmRows[index].destinationIndex)] = index;
        mmRows.pop_back();
    }
    
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
    
    void process();
    void clear();
    
private:
    std::vector<ModulationMatrixRow> mmRows;
    std::unordered_map<int, int> mmRowsMap;
    std::unordered_map<int, double> sources;
    std::unordered_map<int, double> destinations;
};



#endif  // MODULATIONMATRIX_H_INCLUDED
