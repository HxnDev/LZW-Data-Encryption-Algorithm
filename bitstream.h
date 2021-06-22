//--------------------------------------------------------------------------------------------------------------------------------
//  Hassan Shahzad & Azka Khurram
//  18i-0441 & 18i-0461
//  Algo-Project
//  FAST NUCES
//  Task3.cpp
//--------------------------------------------------------------------------------------------------------------------------------
//================================================================================================================================
// 1: This file is used for encoding purposes in "lzw.h"
//================================================================================================================================



#include "dictionary.cpp"
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
using namespace std;
// ========================================================
// class BitStreamWriter:
// ========================================================

class BitStreamWriter final
{
private:

    void internalInit();
    static uint8_t * allocBytes(int bytesWanted, uint8_t * oldPtr, int oldSize);

    uint8_t * stream; 		// Growable buffer to store our bits.
    int bytesAllocated;    // Current size of heap-allocated stream buffer *in bytes*.
    int granularity;       // Amount bytesAllocated multiplies by when auto-resizing in appendBit().
    int currBytePos;       // Current byte being written to, from 0 to bytesAllocated-1.
    int nextBitPos;        // Bit position within the current byte to access next. 0 to 7.
    int numBitsWritten;    // Number of bits in use from the stream buffer, not including byte-rounding padding.
    
public:   

    BitStreamWriter(const BitStreamWriter &) = delete;
    BitStreamWriter & operator = (const BitStreamWriter &) = delete;

    BitStreamWriter();
    explicit BitStreamWriter(int initialSizeInBits, int growthGranularity = 2);

    void allocate(int bitsWanted);
    void setGranularity(int growthGranularity);
    uint8_t * release();

    void appendBit(int bit);
    void appendBitsU64(uint64_t num, int bitCount);

    string toBitString() const;
    void appendBitString(const string & bitStr);

    int getByteCount() const;
    int getBitCount()  const;
    const uint8_t * getBitStream() const;


    ~BitStreamWriter();


};



// ========================================================
// class BitStreamReader:
// ========================================================

class BitStreamReader final
{

private:

    const uint8_t * stream; // Pointer to the external bit stream. Not owned by the reader.
    const int sizeInBytes;       // Size of the stream *in bytes*. Might include padding.
    const int sizeInBits;        // Size of the stream *in bits*, padding *not* include.
    int currBytePos;             // Current byte being read in the stream.
    int nextBitPos;              // Bit position within the current byte to access next. 0 to 7.
    int numBitsRead;             // Total bits read from the stream so far. Never includes byte-rounding padding.


public:

    BitStreamReader(const BitStreamReader &) = delete;
    BitStreamReader & operator = (const BitStreamReader &) = delete;

    BitStreamReader(const BitStreamWriter & bitStreamWriter);
    BitStreamReader(const uint8_t * bitStream, int byteCount, int bitCount);

    bool isEndOfStream() const;
    bool readNextBit(int & bitOut);
    uint64_t readBitsU64(int bitCount);
    void reset();


};
