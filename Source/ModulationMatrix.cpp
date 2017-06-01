/*
  ==============================================================================

    ModulationMatrix.cpp
    Created: 25 Apr 2017 12:19:50pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#include "ModulationMatrix.h"
#include "PluginProcessor.h"

ModulationMatrix::ModulationMatrix()
{
    destinations[ParameterIDFilterCutoff] = 0;
}

void ModulationMatrix::process()
{
    for (auto row : data->getRows())
    {
        destinations[row.destinationIndex] += sources[row.sourceIndex] * row.modulationAmount;
    }
}

void ModulationMatrix::clear()
{
    for (auto row : data->getRows())
    {
        destinations[row.destinationIndex] = 0;
        sources[row.sourceIndex] = 0;
    }
}
