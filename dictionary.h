//--------------------------------------------------------------------------------------------------------------------------------
//  Hassan Shahzad & Azka Khurram
//  18i-0441 & 18i-0461
//  Algo-Project
//  FAST NUCES
//  Task3.cpp
//--------------------------------------------------------------------------------------------------------------------------------
//================================================================================================================================
// 1: This file is used in encoding and decoding. First 256 dictionary entries are reserved to the byte/ASCII range. Additional entries 	
//	follow for the character sequences found in the input. Up to 4096 - 256 (MaxDictEntries - FirstCode).
//================================================================================================================================


#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cassert>
using namespace std;

// ========================================================
// LZW Dictionary helper:
// ========================================================

constexpr int Nil            = -1;
constexpr int MaxDictBits    = 12;
constexpr int StartBits      = 9;
constexpr int FirstCode      = (1 << (StartBits - 1)); // 256
constexpr int MaxDictEntries = (1 << MaxDictBits);     // 4096

class Dictionary final
{
public:

    struct Entry
    {
        int code;
        int value;
    };

    int size;
    Entry entries[MaxDictEntries];

    Dictionary();
    int findIndex(int code, int value) const;
    bool add(int code, int value);
    bool flush(int & codeBitsWidth);
};
