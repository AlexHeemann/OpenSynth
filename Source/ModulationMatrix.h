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
#include "EnvelopeState.h"
#include <memory>

class Module;
class EnvelopeGenerator;
class LFO;

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
    
    std::unordered_map<int, std::shared_ptr<Module>>& getModulators()
    {
        return modulators;
    }
    
    std::shared_ptr<EnvelopeGenerator> getEnvelopeById(int ID)
    {
        if (envelopes.find(ID) != envelopes.end())
        {
            return envelopes[ID];
        }
        else
        {
            return nullptr;
        }
    }
    
    void addLFO(std::shared_ptr<LFO> lfo);
    void addEnvelope(std::shared_ptr<EnvelopeGenerator> envelope);
    
    void removeLFO(int lfoID);
    void removeEnvelope(int envelopeID);
    
    void calculateModulation(int numSamples);
    void writeModulation();
    
    void process();
    void clear();
    void resetModulators();
    void setSampleRateForModulators(int sampleRate);
    
    void setEnvelopeState(EnvelopeState state);
    void setAmpEnvelope(std::shared_ptr<EnvelopeGenerator> envelope)
    {
        this->ampEnvelope = envelope;
    }
    std::shared_ptr<EnvelopeGenerator> getAmpEnvelope() { return ampEnvelope; }
    
private:
    std::unordered_map<int, double> sources;
    std::unordered_map<int, double> destinations;
    ModulationMatrixData* data;
    
    std::unordered_map<int, std::shared_ptr<Module>> modulators;
    std::unordered_map<int, std::shared_ptr<EnvelopeGenerator>> envelopes;
    std::unordered_map<int, std::shared_ptr<LFO>> lfos;
    std::shared_ptr<EnvelopeGenerator> ampEnvelope;
    
    void addModulator(std::shared_ptr<Module> modulator);
    void removeModulator(int modulatorID);
};



#endif  // MODULATIONMATRIX_H_INCLUDED
