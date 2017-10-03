/*
  ==============================================================================

    IDManager.h
    Created: 8 Aug 2017 8:31:23pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

#include <queue>

class IDManager
{
public:
    IDManager() {}
    ~IDManager() {}
    
    void freeID(int ID)
    {
        freeIDs.push(ID);
    }
    
    int getNewID()
    {
        if (!freeIDs.empty())
        {
            int front =  freeIDs.front();
            freeIDs.pop();
            return front;
        }
        else
        {
            return currentID++;
        }
    }
    
private:
    std::queue<int> freeIDs;
    int currentID = 0;
};
