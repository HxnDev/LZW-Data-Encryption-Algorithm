//--------------------------------------------------------------------------------------------------------------------------------
//  Hassan Shahzad & Azka Khurram
//  18i-0441 & 18i-0461
//  Algo-Project
//  FAST NUCES
//  Task3.cpp
//--------------------------------------------------------------------------------------------------------------------------------
//================================================================================================================================
// 1: This file is used to call all the functions and this class is basic interaction between the client and the system. For part 3
//    we have implemented an algorithm technique that compresses the file along with encoding it. This algorithm is called "LZW".
// 2: LZW = Lempel-Ziv-Welch. It is a universal lossless data compression algorithm. No data is loss during this compression. It is 
//    usually used in GIFs and PDFs. For this programming, we created a header library instead of a header file as we wanted to post
//    this code on our github later on.
//================================================================================================================================


#include "lzw.cpp"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace lzw;

static void LZW(const uint8_t * sampleData, const int sampleSize)			//Implementation of LZW ALgorithm
{
    int compressedSizeBytes = 0;
    int compressedSizeBits  = 0;
    uint8_t * compressedData = nullptr;
    vector<uint8_t> uncompressedBuffer(sampleSize, 0);



//----------------------------------------------------------------------------------------------------------------------------------
    easyEncode(sampleData, sampleSize, &compressedData,&compressedSizeBytes, &compressedSizeBits);			//Encoding
  
  	cout << "LZW uncompressed size bytes = " << sampleSize << "\n";
	cout << "LZW compressed size bytes   = " << compressedSizeBytes << "\n\n";
	
	ofstream out("encoded.txt");
	for (int i = 0; i < compressedSizeBytes; i++) 
	{
    	out << compressedData[i];
    }
	out.close();
//----------------------------------------------------------------------------------------------------------------------------------	

    const int uncompressedSize = easyDecode(compressedData, compressedSizeBytes, compressedSizeBits, uncompressedBuffer.data(), uncompressedBuffer.size());				//Decoding
                                                 
    ofstream out2("decoded.txt");
    for (int i = 0; i < uncompressedBuffer.size(); i++) 
    {
    	out2 << uncompressedBuffer[i];
    }
    
    out2.close();
    
	cout << "LZW decompressed size bytes   = " << uncompressedBuffer.size() << "\n\n";


//----------------------------------------------------------------------------------------------------------------------------------


    bool successful = true;
    if (uncompressedSize != sampleSize)					// comparing sizes
    {
        cout << "LZW COMPRESSION ERROR! Size mismatch!\n";
        successful = false;
    }
    
//----------------------------------------------------------------------------------------------------------------------------------

    
    if (memcmp(uncompressedBuffer.data(), sampleData, sampleSize) != 0)				//Comparing data
    {
        cout << "The files are not same. Data has been corrupted!\n";
        successful = false;
    }

    if (successful)
    {
        cout << "LZW compression successful!\n";
    }

    free(compressedData);

}

//----------------------------------------------------------------------------------------------------------------------------------
//															Main starts here
//----------------------------------------------------------------------------------------------------------------------------------



int main() 
{

//----------------------------------------------------------------------------------------------------------------------------------

	cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
	cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
	cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "\t \t \t Design and Analysis of Algorithm" << endl;
	cout << "\t \t \t End of Semester Project" << endl<<endl;
	cout << "\t \t \t Task 3 (LZW Data Compression & Decompression Algorithm)" << endl<<endl;
	cout << "\t \t \t Hassan Shahzad & Azka Khurram" << endl;
	cout << "\t \t \t\t 18i-0441 & 18i-0461" << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;
	cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
	cout << endl << "----------------------------------------------------------------------------------------------------" << endl;
//----------------------------------------------------------------------------------------------------------------------------------
	
	string str,filename;
	
	cout<<"Enter the name of the file without the extension = ";
	cin>>filename;	
	ifstream in(filename + ".txt");
	if (in)
	{
		char c = in.get();
		while (!in.eof()) 
		{
			cout<<"Waiting..."<<endl;
			str += c;
			c = in.get();
		}
		in.close();
	}
	
	
	cout << "Bytes read from file = " << str.size() << endl;
	
	
	vector<uint8_t> myVector(str.begin(), str.end());
	static const uint8_t* str0 = &myVector[0];
	
	LZW(str0, str.size());
	
}
