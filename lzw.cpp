//--------------------------------------------------------------------------------------------------------------------------------
//  Hassan Shahzad & Azka Khurram
//  18i-0441 & 18i-0461
//  Algo-Project
//  FAST NUCES
//  Task3.cpp
//--------------------------------------------------------------------------------------------------------------------------------
//================================================================================================================================
// 1: This file is basically the implementation of "lzw.h". It consists all the functionalities and definitions of fucntions.
//================================================================================================================================

#include "lzw.h"
namespace lzw
{
// ================================================================================================
//
//                                     LZW Implementation
//
// ================================================================================================



// ========================================================
// 					Encoding implementation:
// ========================================================

void easyEncode(const uint8_t * uncompressed, int uncompressedSizeBytes,
                uint8_t ** compressed, int * compressedSizeBytes, int * compressedSizeBits)
{
    if (uncompressed == nullptr || compressed == nullptr)
    {
        cout<<"easyEncode(): Null data pointer(s)!"<<endl;
        return;
    }

    if (uncompressedSizeBytes <= 0 || compressedSizeBytes == nullptr || compressedSizeBits == nullptr)
    {
        cout<<"easyEncode(): Bad in/out sizes!"<<endl;
        return;
    }

    // LZW encoding context:
    int code = Nil;
    int codeBitsWidth = StartBits;
    Dictionary dictionary;

    // Output bit stream we write to. This will allocate
    // memory as needed to accommodate the encoded data.
    BitStreamWriter bitStream;

    for (; uncompressedSizeBytes > 0; --uncompressedSizeBytes, ++uncompressed)
    {
        const int value = *uncompressed;
        const int index = dictionary.findIndex(code, value);

        if (index != Nil)
        {
            code = index;
            continue;
        }

        // Write the dictionary code using the minimum bit-with:
        bitStream.appendBitsU64(code, codeBitsWidth);

        // Flush it when full so we can restart the sequences.
        if (!dictionary.flush(codeBitsWidth))
        {
            // There's still space for this sequence.
            dictionary.add(code, value);
        }
        code = value;
    }

    // Residual code at the end:
    if (code != Nil)
    {
        bitStream.appendBitsU64(code, codeBitsWidth);
    }

    // Pass ownership of the compressed data buffer to the user pointer:
    *compressedSizeBytes = bitStream.getByteCount();
    *compressedSizeBits  = bitStream.getBitCount();
    *compressed          = bitStream.release();
}

// ========================================================
// 				Decoding implementation:
// ========================================================

static bool outputByte(int code, uint8_t *& output, int outputSizeBytes, int & bytesDecodedSoFar)
{
    if (bytesDecodedSoFar >= outputSizeBytes)
    {
    	cout<<"Decoder output buffer too small!"<<endl;
        return false;
    }

    assert(code >= 0 && code < 256);
    *output++ = static_cast<uint8_t>(code);
    ++bytesDecodedSoFar;
    return true;
}

static bool outputSequence(const Dictionary & dict, int code,
                           uint8_t *& output, int outputSizeBytes,
                           int & bytesDecodedSoFar, int & firstByte)
{
    // A sequence is stored backwards, so we have to write
    // it to a temp then output the buffer in reverse.
    int i = 0;
    uint8_t sequence[MaxDictEntries];
    do
    {
        assert(i < MaxDictEntries - 1 && code >= 0);
        sequence[i++] = dict.entries[code].value;
        code = dict.entries[code].code;
    }
    while (code >= 0);

    firstByte = sequence[--i];
    for (; i >= 0; --i)
    {
        if (!outputByte(sequence[i], output, outputSizeBytes, bytesDecodedSoFar))
        {
            return false;
        }
    }
    return true;
}

int easyDecode(const uint8_t * compressed, const int compressedSizeBytes, const int compressedSizeBits,
              uint8_t * uncompressed, const int uncompressedSizeBytes)
{
    if (compressed == nullptr || uncompressed == nullptr)
    {
    	cout<<"easyDecode(): Null data pointer(s)!"<<endl;
    	return 0;
    }

    if (compressedSizeBytes <= 0 || compressedSizeBits <= 0 || uncompressedSizeBytes <= 0)
    {
        cout<<"easyDecode(): Bad in/out sizes!"<<endl;
        return 0;
    }

    int code          = Nil;
    int prevCode      = Nil;
    int firstByte     = 0;
    int bytesDecoded  = 0;
    int codeBitsWidth = StartBits;

    // We'll reconstruct the dictionary based on the
    // bit stream codes. Unlike Huffman encoding, we
    // don't store the dictionary as a prefix to the data.
    Dictionary dictionary;
    BitStreamReader bitStream(compressed, compressedSizeBytes, compressedSizeBits);

    // We check to avoid an overflow of the user buffer.
    // If the buffer is smaller than the decompressed size,
    // LZW_ERROR() is called. If that doesn't throw or
    // terminate we break the loop and return the current
    // decompression count.
    while (!bitStream.isEndOfStream())
    {
        assert(codeBitsWidth <= MaxDictBits);
        code = static_cast<int>(bitStream.readBitsU64(codeBitsWidth));

        if (prevCode == Nil)
        {
            if (!outputByte(code, uncompressed,
                 uncompressedSizeBytes, bytesDecoded))
            {
                break;
            }
            firstByte = code;
            prevCode  = code;
            continue;
        }

        if (code >= dictionary.size)
        {
            if (!outputSequence(dictionary, prevCode, uncompressed,
                 uncompressedSizeBytes, bytesDecoded, firstByte))
            {
                break;
            }
            if (!outputByte(firstByte, uncompressed,
                 uncompressedSizeBytes, bytesDecoded))
            {
                break;
            }
        }
        else
        {
            if (!outputSequence(dictionary, code, uncompressed,
                 uncompressedSizeBytes, bytesDecoded, firstByte))
            {
                break;
            }
        }

        dictionary.add(prevCode, firstByte);
        if (dictionary.flush(codeBitsWidth))
        {
            prevCode = Nil;
        }
        else
        {
            prevCode = code;
        }
    }

    return bytesDecoded;
}

}
