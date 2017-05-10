/*
  ==============================================================================

    DragAndDropListener.h
    Created: 6 May 2017 6:40:32pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

class DragAndDropListener
{
public:
    virtual ~DragAndDropListener() {};
    virtual void itemDropped(const int sourceID, const int destinationID) = 0;
};
