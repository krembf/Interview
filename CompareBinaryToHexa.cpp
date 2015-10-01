/* 
Objective:
Write a function to check if the value of a binary number (passed as a string) equals the hexadecimal representation of a string.


The numbers 0000000111010010 and 01D2 are Equal
 */


#include <iostream>
#include <map>
using namespace std;


// To execute C++, please define "int main()"


map<string,unsigned int> binaryMap;
map<string,unsigned int> hexadecimalMap;


void MapInit()
{
  //binary map
  binaryMap["0000"] = 0x0;
  binaryMap["0001"] = 0x1;
  binaryMap["0010"] = 0x2;
  binaryMap["0011"] = 0x3;
  binaryMap["0100"] = 0x4;
  binaryMap["0101"] = 0x5;
  binaryMap["0110"] = 0x6;
  binaryMap["0111"] = 0x7;
  binaryMap["1000"] = 0x8;
  binaryMap["1001"] = 0x9;
  binaryMap["1010"] = 0xA;
  binaryMap["1011"] = 0xB;
  binaryMap["1100"] = 0xC;
  binaryMap["1101"] = 0xD;
  binaryMap["1110"] = 0xE;
  binaryMap["1111"] = 0xF;  
  
  //hexadecimal map
  hexadecimalMap["0"] = 0x0;
  hexadecimalMap["1"] = 0x1;
  hexadecimalMap["2"] = 0x2;
  hexadecimalMap["3"] = 0x3;
  hexadecimalMap["4"] = 0x4;
  hexadecimalMap["5"] = 0x5;
  hexadecimalMap["6"] = 0x6;
  hexadecimalMap["7"] = 0x7;
  hexadecimalMap["8"] = 0x8;
  hexadecimalMap["9"] = 0x9;
  hexadecimalMap["A"] = 0xA;
  hexadecimalMap["B"] = 0xB;
  hexadecimalMap["C"] = 0xC;
  hexadecimalMap["D"] = 0xD;
  hexadecimalMap["E"] = 0xE;
  hexadecimalMap["F"] = 0xF;      
}


unsigned int Binary2Int(string sBinaryNumber)
{
  if(binaryMap.find(sBinaryNumber) != binaryMap.end())
  {
    cout<<"[Binary2Int] number "<<sBinaryNumber<<" found in map"<<endl;
    return binaryMap[sBinaryNumber];
  }
  
  cout<<"[Binary2Int] Throwing exception"<<endl;
  throw (exception());
}


unsigned int Hexadecimal2Int(string sHexadecimalNumber)
{
  if(hexadecimalMap.find(sHexadecimalNumber) != hexadecimalMap.end())
  {
    cout<<"[Hexadecimal2Int] number "<<sHexadecimalNumber<<" found in map"<<endl;
    return hexadecimalMap[sHexadecimalNumber];
  }
  
  cout<<"[Hexadecimal2Int] Throwing exception"<<endl;
  throw (exception());
}




bool AreEqual(string sBinary, string sHexadecimal)
{
  int i = sBinary.size();
  int j = sHexadecimal.size();
  string sBinaryNumber, sHexadecimalNumber;
  
  if( i == 0 || j == 0 )
  {
    cout<<"[AreEqual] Throwing exception";
    throw(exception());
  }
  
  while( i > 0 && j > 0 )
  {
    //extract the numbers
    sBinaryNumber = sBinary.substr( i - 4, 4 );
    sHexadecimalNumber = sHexadecimal.substr( j - 1, 1 );
    
    try
    {
      if(Binary2Int(sBinaryNumber) != Hexadecimal2Int(sHexadecimalNumber))
      {
        return false;
      }
    }
    catch(exception &ex)
    {
      throw(ex);
    }
    
    i-=4; j-=1;
  }
  
  if( i > 0 || j > 0 )
  {
    return false;
  }
  
  return true;
}




int main() {
  cout<<"Objective: Write a function to check if the value of a binary number"<<endl;
  cout<<"(passed as a string) equals the hexadecimal representation of a string."<<endl<<endl;
  
  string A = "0000000111010010";
  string B = "01D2";
  MapInit();
  
  try
  {
    cout<<"The numbers "<<A<<" and "<<B<<" are "<<(AreEqual(A, B)?"Equal":"Not Equal");
  }
  catch(exception &ex)
  {
    cout<<"Exception: Invalid format - "<<ex.what();
  }
  
  return 0;
}