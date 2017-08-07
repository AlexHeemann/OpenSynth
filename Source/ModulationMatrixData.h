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
#include "RingBuffer.h"

static const int kModulationChangesRingBufferSize = 100;

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

struct ModulationChange
{
public:
    typedef enum
    {
        TypeAdd,
        TypeRemove,
    } Type;
    
    ModulationChange(ModulationChange::Type type, int sourceID, int destinationID) :
    type(type),
    sourceID(sourceID),
    destinationID(destinationID) {}
    
    ModulationChange() {}
    ~ModulationChange() {}
    
    Type type = TypeAdd;
    int sourceID = 0;
    int destinationID = 0;
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
    
    void connect(int sourceID, int destinationID)
    {
        addRow(sourceID, destinationID, 1.0, mmRowsInterface, mmRowsMapInterface);
        
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
        
        modulationChanges.feed(ModulationChange(ModulationChange::TypeAdd, sourceID, destinationID));
    }
    
    void disconnect(int sourceID, int destinationID)
    {
        removeRow(sourceID, destinationID, mmRowsInterface, mmRowsMapInterface);
        destinationToModMap[destinationID]->remove(sourceID);
        modulationChanges.feed(ModulationChange(ModulationChange::TypeRemove, sourceID, destinationID));
    }
    
    void updateModulationAmount(int sourceID, int destinationID, double modulationAmount)
    {
        int index = mmRowsMapInterface[keyFromIDs(sourceID, destinationID)];
        mmRowsInterface[index].modulationAmount = modulationAmount;
    }
    
    // To be called from the UI
    double getModulationAmount(int sourceID, int destinationID)
    {
        int index = mmRowsMapInterface[keyFromIDs(sourceID, destinationID)];
        return mmRowsInterface[index].modulationAmount;
    }
    
    bool containsConnection(int sourceID, int destinationID)
    {
        int key = keyFromIDs(sourceID, destinationID);
        return (mmRowsMap.find(key) != mmRowsMap.end());
    }
    
    bool removeRow(int sourceID,
                   int destinationID,
                   std::vector<ModulationMatrixRow>& rows,
                   std::unordered_map<int, int>& map)
    {
        int key = keyFromIDs(sourceID, destinationID);
        if (map.find(key) == map.end())
        {
            return false;
        }
        int index = map[key];
        int lastIndex = (int)rows.size() - 1;
        map.erase(key);
        if (index != lastIndex)
        {
            // Copy last element into removed spot and update index in map
            rows[index] = rows[mmRows.size() - 1];
            map[keyFromIDs(mmRows[index].sourceIndex, mmRows[index].destinationIndex)] = index;
        }
        rows.pop_back();
        
        return true;
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
    
    void processModulationChanges();
    
private:
    
    void addRow(int sourceID,
                int destinationID,
                double modulationAmount,
                std::vector<ModulationMatrixRow>& rows,
                std::unordered_map<int, int>& map)
    {
        ModulationMatrixRow row = ModulationMatrixRow(sourceID, destinationID, modulationAmount);
        rows.push_back(row);
        map[keyFromIDs(sourceID, destinationID)] = (int)rows.size() - 1;
    }
    
    std::unordered_map<int, std::string> sourceNames;
    std::vector<ModulationMatrixRow> mmRows;
    std::vector<ModulationMatrixRow> mmRowsInterface; // For separation of UI thread and audio thread
    std::unordered_map<int, int> mmRowsMap;
    std::unordered_map<int, int> mmRowsMapInterface;
    std::unordered_map<int, std::unique_ptr<std::list<int>>> destinationToModMap; // Maps to list of modulation source IDs from destination ID
    RingBuffer<kModulationChangesRingBufferSize, ModulationChange> modulationChanges;
};
