//--------------------------------------------------------------------------------------------------------------------------------
//  Hassan Shahzad & Azka Khurram
//  18i-0441 & 18i-0461
//  Algo-Project
//  FAST NUCES
//  Task3.cpp
//--------------------------------------------------------------------------------------------------------------------------------
//================================================================================================================================
// 1: This file is basically a header file for LZW Data compression algorithm. This file consists of all of the implementation
//    part from encoding to decoding and other functionalities.
//================================================================================================================================


#include "bitstream.cpp"
#include<iostream>
#include <cstdint>
#include <cstdlib>
#include <string>


using namespace std;
namespace lzw
{

// ========================================================
// Encoding:
// ========================================================

void easyEncode(const uint8_t * uncompressed, int uncompressedSizeBytes, uint8_t ** compressed, int * compressedSizeBytes, int * compressedSizeBits);

// ========================================================
// Decoding:
// ========================================================

int easyDecode(const uint8_t * compressed, int compressedSizeBytes, int compressedSizeBits, uint8_t * uncompressed, int uncompressedSizeBytes);

}



