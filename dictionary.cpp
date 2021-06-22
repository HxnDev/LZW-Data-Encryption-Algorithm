//--------------------------------------------------------------------------------------------------------------------------------
//  Hassan Shahzad & Azka Khurram
//  18i-0441 & 18i-0461
//  Algo-Project
//  FAST NUCES
//  Task3.cpp
//--------------------------------------------------------------------------------------------------------------------------------
//================================================================================================================================
// 1: This file is basically an implementation of header file "dictionary.h"
//================================================================================================================================



#include "dictionary.h"
// ========================================================
// class Dictionary:
// ========================================================

Dictionary::Dictionary()
{
    size = FirstCode;
    for (int i = 0; i < size; ++i)
    {
        entries[i].code  = Nil;
        entries[i].value = i;
    }
}

int Dictionary::findIndex(const int code, const int value) const
{
    if (code == Nil)
    {
        return value;
    }

    // Linear search
    for (int i = 0; i < size; ++i)
    {
        if (entries[i].code == code && entries[i].value == value)
        {
            return i;
        }
    }

    return Nil;
}

bool Dictionary::add(const int code, const int value)
{
    if (size == MaxDictEntries)
    {
    	cout<<"Dictionary overflowed!"<<endl;
        return false;
    }

    entries[size].code  = code;
    entries[size].value = value;
    ++size;
    return true;
}

bool Dictionary::flush(int & codeBitsWidth)
{
    if (size == (1 << codeBitsWidth))
    {
        ++codeBitsWidth;
        if (codeBitsWidth > MaxDictBits)
        {
            // Clear the dictionary (except the first 256 byte entries).
            codeBitsWidth = StartBits;
            size = FirstCode;
            return true;
        }
    }
    return false;
}
