/*
  ==============================================================================

    ModulationMatrixData.h
    Created: 1 Jun 2017 6:14:17am
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include <unordered_map>
#include <list>

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


class ModulationMatrixData
{
public:
    ModulationMatrixData() {};
    ~ModulationMatrixData() {};
    
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
    
    double getModulationAmount(int sourceID, int destinationID)
    {
        int index = mmRowsMap[keyFromIDs(sourceID, destinationID)];
        return mmRows[index].modulationAmount;
    }
    
    void addRow(int sourceID, int destinationID, double modulationAmount)
    {
        ModulationMatrixRow row = ModulationMatrixRow(sourceID, destinationID, modulationAmount);
        mmRows.push_back(row);
        mmRowsMap[keyFromIDs(sourceID, destinationID)] = mmRows.size() - 1;
        
        if (destinationToModMap.find(destinationID) == destinationToModMap.end())
        {
            std::unique_ptr<std::list<int>> p(new std::list<int>());
            p->push_back(sourceID);
            destinationToModMap[destinationID] = std::move(p);
        }
        else
        {
            destinationToModMap[destinationID]->push_back(sourceID);
        }
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
        
        destinationToModMap[destinationID]->remove(sourceID);
    }
    
    std::unordered_map<int, std::unique_ptr<std::list<int>>>& getDestinationToModMap()
    {
        return destinationToModMap;
    }
    
    std::list<int>* getSourcesForDestination(int destinationID)
    {
        if (destinationToModMap.find(destinationID) != destinationToModMap.end())
        {
            return destinationToModMap[destinationID].get();
        }
        return nullptr;
    }
    
    void setRows(std::vector<ModulationMatrixRow> mmRows)
    {
        this->mmRows = mmRows;
    }
    
    std::vector<ModulationMatrixRow>& getRows()
    {
        return mmRows;
    }
    
    void setSourceName(int source, std::string name)
    {
        sourceNames[source] = name;
    }
    
    std::string& getSourceName(int source)
    {
        return sourceNames[source];
    }
    
private:
    std::unordered_map<int, std::string> sourceNames;
    std::vector<ModulationMatrixRow> mmRows;
    std::unordered_map<int, int> mmRowsMap;
    std::unordered_map<int, std::unique_ptr<std::list<int>>> destinationToModMap; // Maps to list of modulation source IDs from destination ID
};
