#include <iostream>
#include <vector>
#include <windows.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <windows.h>
#include <time.h> 
#include <queue>

using namespace std;

typedef vector<int> ARRAY_INT;

ARRAY_INT Merge(ARRAY_INT A1, ARRAY_INT A2)
{
  ARRAY_INT AHelp;

  unsigned int m = 0, n = 0;

  while(m < A1.size() && n < A2.size())
  {
    if(A1[m] <= A2[n]) { AHelp.push_back(A1[m++]); }
    else { AHelp.push_back(A2[n++]); }; 
  }
  if(m == A1.size()) while (n < A2.size()) { AHelp.push_back(A2[n++]); }
  else if(n == A2.size()) while (m < A1.size()) { AHelp.push_back(A1[m++]); }

  return AHelp;
}

ARRAY_INT Merge_Sort(ARRAY_INT A, int p, int r)
{
  ARRAY_INT AHelp;
  ARRAY_INT A1;
  ARRAY_INT A2;
  int middle;

  if(p >= r) { 
    AHelp.push_back(A[r]); 
    return AHelp; 
  }
  middle = (r+p)/2;
  A1 = Merge_Sort(A, p, middle);
  A2 = Merge_Sort(A, middle+1, r);

  return Merge(A1, A2);
}

/**
  Merge Sort

  Singlethreaded

  @param void
  @return void
*/
void Test3()
{
  LARGE_INTEGER frequency;        // ticks per second
  LARGE_INTEGER t1, t2;           // ticks
  double elapsedTime;

  ARRAY_INT A;
  cout<<endl<<"Unsorted Array:"<<endl;
  for(int i = 0; i < 1000; i++)
  {
    A.push_back(rand()%100);
    cout<<A[i]<< ' ';
  }

  cout<<endl<<endl;

  // get ticks per second
  QueryPerformanceFrequency(&frequency);
  
  // start timer
  QueryPerformanceCounter(&t1);

  ARRAY_INT ARes = Merge_Sort(A, 0, A.size()-1);

  // stop timer
  QueryPerformanceCounter(&t2);
  
  // compute and print the elapsed time in millisec
  elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

  cout<<endl<<"Sorted Array: "<<endl;
  for(unsigned int i = 0; i < ARes.size(); i++)
    cout<<ARes[i]<< ' ';
  cout<<endl<<"Execution time "<<elapsedTime<<" seconds"<<endl;
}

typedef struct thread_param
{
  ARRAY_INT &A;
  int p;
  int r;
  ARRAY_INT ARes;
} THREAD_PARAM;

#define MAX_THREADS 2

DWORD WINAPI Merge_Sort_MT( LPVOID lpParam ) 
{
  THREAD_PARAM *param_in = (THREAD_PARAM *) lpParam;
  int middle;
  DWORD   dwThreadIdArray[MAX_THREADS];
  HANDLE  hThreadArray[2]; 

  if(param_in->p >= param_in->r) { 
    param_in->ARes.push_back(param_in->A[param_in->r]); 
    return 0;
  }

  middle = (param_in->r+param_in->p)/2;

  THREAD_PARAM param_out1 = { param_in->A, param_in->p, middle};
  THREAD_PARAM param_out2 = { param_in->A, middle+1, param_in->r};

  hThreadArray[0] = CreateThread( 
    NULL,                   // default security attributes
    0,                      // use default stack size  
    Merge_Sort_MT,      // thread function name
    &param_out1,      // argument to thread function 
    0,                      // use default creation flags 
    &dwThreadIdArray[0]);   // returns the thread identifier 

  if (hThreadArray[0] == NULL) 
  {
    cout<<(TEXT("CreateThread failed"));
    return 0;
  }
  else
  {
    //cout<<"\n Thread created, ID "<<dwThreadIdArray[0];
  }

  hThreadArray[1] = CreateThread( 
    NULL,                   // default security attributes
    0,                      // use default stack size  
    Merge_Sort_MT,       // thread function name
    &param_out2,          // argument to thread function 
    0,                      // use default creation flags 
    &dwThreadIdArray[1]);   // returns the thread identifier 

  if (hThreadArray[1] == NULL) 
  {
    cout<<(TEXT("CreateThread failed"));
    return 0;
  }
  else
  {
    //cout<<"\n Thread created, ID "<<dwThreadIdArray[1];
  }

  WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

  param_in->ARes = Merge(param_out1.ARes, param_out2.ARes);

  return 0;
}

/**
  Merge Sort

  Multithreaded

  @param void
  @return void
*/
void Test4()
{
  LARGE_INTEGER frequency;        // ticks per second
  LARGE_INTEGER t1, t2;           // ticks
  double elapsedTime;

  ARRAY_INT A;
  cout<<endl<<"Unsorted Array:"<<endl;
  for(int i = 0; i < 1000; i++)
  {
    A.push_back(rand()%100);
    cout<<A[i]<< ' ';
  }  
  
  cout<<endl<<endl;

  THREAD_PARAM param = { A, 0, A.size()-1};
  
  // get ticks per second
  QueryPerformanceFrequency(&frequency);
  
  // start timer
  QueryPerformanceCounter(&t1);

  Merge_Sort_MT(&param);
  
  // stop timer
  QueryPerformanceCounter(&t2);
  
  // compute and print the elapsed time in millisec
  elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

  cout<<endl<<"Sorted Array:"<<endl;
  for(unsigned int i = 0; i < param.ARes.size(); i++)
    cout<<param.ARes[i]<< ' ';
  cout<<endl<<"Execution time "<<elapsedTime<<" msec"<<endl;
}


int main() {
  
  Test3();
  Test4();
  
  return 0;
}
