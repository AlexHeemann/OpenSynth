/*
  ==============================================================================

    RingBuffer.h
    Created: 2 Aug 2017 4:36:46pm
    Author:  Alexander Heemann

  ==============================================================================
*/

#pragma once

template<const int _LENGTH, typename T = float>
class RingBuffer
{
public:
    enum { LENGTH = _LENGTH };
    
    volatile int readpos = 0;
    volatile int writepos = 0;
    T buffer[LENGTH];
    
    inline bool read(T& val)
    {
        int r = readpos;
        if (r == writepos)
            return false;
        r = (r == LENGTH - 1) ? 0 : (r + 1);
        val = buffer[r];
        readpos = r;
        return true;
    }
    
    inline void skip(int num)
    {
        int r = readpos + num;
        if (r >= LENGTH)
            r -= LENGTH;
        readpos = r;
    }
    
    inline void syncWritePos()
    {
        writepos = readpos;
    }
    
    inline bool feed(const T& input)
    {
        int w = (writepos == LENGTH - 1) ? 0 : (writepos + 1);
        buffer[w] = input;
        writepos = w;
        return true;
    }
    
    inline int getNumBuffered() const
    {
        int b = writepos - readpos;
        if (b < 0)
            b += LENGTH;
        return b;
    }
    
    inline void clear()
    {
        writepos = 0;
        readpos = 0;
    }
};
