/*
  ==============================================================================

    ModulationMatrixData.cpp
    Created: 1 Jun 2017 6:14:17am
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "ModulationMatrixData.h"

void ModulationMatrixData::processModulationChanges()
{
    ModulationChange modulationChange;
    while (modulationChanges.read(modulationChange))
    {
        switch (modulationChange.type)
        {
            case ModulationChange::TypeAdd:
                if (!containsConnection(modulationChange.sourceID, modulationChange.destinationID))
                {
                    addRow(modulationChange.sourceID, modulationChange.destinationID, 1.0, mmRows, mmRowsMap);
                }
                break;
            case ModulationChange::TypeRemove:
                removeRow(modulationChange.sourceID, modulationChange.destinationID, mmRows, mmRowsMap);
                break;
        }
    }
    
    for (auto& row : mmRowsInterface)
    {
        int key = keyFromIDs(row.sourceIndex, row.destinationIndex);
        mmRows[mmRowsMap[key]].modulationAmount = row.modulationAmount;
    }
}
