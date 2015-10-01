/* 
Objective:
<p>Given a matrix containing 0 and 1. Consider 1 as 'Land' and 0 as 'Water'. Find out the number of 'Islands' in the matrix. That is, set of all adjacent 1 will make up for an island.
<br>
<br>For example:
<br>
<br>[ 0 1 1 0 1 ]
<br>[ 1 1 1 0 0 ]
<br>[ 0 0 0 1 1 ]
<br>[ 1 0 0 1 0 ]
<br>
<br>This problem has 4 islands. ( consider set of 1s, vertically, horizontally and diagonally ).</p>
 */




#include <iostream>
using namespace std;


// To execute C++, please define "int main()"


#define SIZE_M 5
#define SIZE_N 5
#define NON_COLORED -1
#define SEA 0
#define SOIL 1
int iMatrix [SIZE_M][SIZE_N] = { {0, 1, 0, 0, 1}, {1, 1, 0, 1, 0}, {1, 0, 0, 0, 1}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 1}};
//Not real initialization here, must be initialized later with values
int iHelpMatrix[SIZE_M][SIZE_N] = {0};


bool FindIsland(int i, int j, int iNumIslands) {
  if(i < 0 || j < 0) return false;
  if(i > SIZE_M || j > SIZE_N) return false;
  if(!(iHelpMatrix[i][j] == NON_COLORED)) return false;
  if(iMatrix[i][j] == SEA) { iHelpMatrix[i][j] = SEA; return false; }
  
  iHelpMatrix[i][j] = iNumIslands + 1;
  
  for(int k = -1; k < 2; k++)
    for(int l = -1; l < 2; l++) {
      if(!(k==0 && l==0)) FindIsland(i+k, j+l, iNumIslands+1);
    }
  
  return true;
}


int main() {
  int i, j;
  int iNumIslands = 0;
  
  //Initialize iHelpMatrix
  for (i = 0; i < SIZE_M; i++) {
    for (j = 0; j < SIZE_N; j++) {
      iHelpMatrix[i][j] = NON_COLORED;
    }
  }      
  
  for (int i = 0; i < SIZE_M; i++) {
    for (int j = 0; j < SIZE_N; j++) {
      iNumIslands = (FindIsland(i, j, iNumIslands))?iNumIslands+1:iNumIslands;
    }
  }
  
  cout<<"Number of Islands found: "<<iNumIslands;
  return 0;
}