/* 
Objective:
Numbers are randomly generated and stored into an (expanding) array. How would you keep track of the median?


After inserting 1, median is 1
After inserting 2, median is 1.5
After inserting 8, median is 2
After inserting -1, median is 1.5
After inserting -6, median is 1
After inserting 0, median is 0.5
After inserting 3, median is 1
After inserting 5, median is 1.5
 */


#include <iostream>
using namespace std;


// To execute C++, please define "int main()"


typedef bool (*COMPARATOR)(float, float);


bool Ascending(float f1, float f2)
{
  return (f1 <= f2);
}


bool Descending(float f1, float f2)
{
  return (f1 > f2);
}


typedef struct Node_ts
{
  float item;
  Node_ts *next;
  Node_ts *prev;
} NODE, *NODE_PTR, **NODE_PTR_PTR;


void AddSorted(NODE_PTR_PTR node, float item, COMPARATOR comparator)
{
  NODE_PTR iter;
  NODE_PTR newnode;
  
  //cout<<"[AddSorted] item "<<item<<endl;
  
  if(NULL == *node)
  {
    *node = (NODE_PTR)malloc(sizeof(NODE));
    (*node)->item = item;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    return;
  }
  
  //create new node
  newnode = (NODE_PTR) malloc(sizeof(NODE));
  newnode->item = item;
  newnode->next = NULL;
  newnode->prev = NULL;  
  
  iter = *node;
  while((comparator(iter->item, newnode->item)) && (iter->next != NULL))
  {
    iter = iter->next;
  }
    
  if(comparator(iter->item, newnode->item))
  {
    //cout<<"[AddSorted] comparator true"<<endl;
    if(iter->next == NULL)
    {
      iter->next = newnode;
      newnode->prev = iter;
    }
    else
    {
      newnode->next = iter->next;
      newnode->prev = iter;
      iter->next->prev = newnode;
      iter->next = newnode;
    }
  }
  else
  {
    //cout<<"[AddSorted] comparator false"<<endl;
    if(iter->prev == NULL)
    {
      //cout<<"[AddSorted] adding "<<item<<" as first node"<<endl;
      iter->prev = newnode;
      newnode->next = iter;
      *node = newnode;
    }
    else
    {
      newnode->prev = iter->prev;
      newnode->next = iter;
      iter->prev->next = newnode;
      iter->prev = newnode;
    }
  }  
}
 
float PullFirst(NODE_PTR_PTR node)
{
  NODE_PTR tempNode = (*node);
  float tempItem = tempNode->item;
  (*node) = (*node)->next;
  if((*node != NULL))
    (*node)->prev = NULL;
  
  delete tempNode;
  
  return tempItem;
}


typedef struct MedianCollection_ts
{
  int cnt;
  float fMedian;
  NODE_PTR npLeft;
  NODE_PTR npRight;
} MEDIAN_COLLECTION, *MEDIAN_COLLECTION_PTR;


float Insert(MEDIAN_COLLECTION_PTR coll, float value)
{
  if(coll->cnt == 0)
  {
    coll->fMedian = value;
    coll->cnt++;
    return coll->fMedian;
  }
  
  if(coll->cnt%2) //odd to even
  {
    //cout<<"[odd to even]"<<endl;
    coll->cnt++;
    if(value > coll->fMedian)
    {
      AddSorted(&coll->npRight, value, Ascending);
      AddSorted(&coll->npLeft, coll->fMedian, Descending);
    }
    else
    {
      AddSorted(&coll->npLeft, value, Descending);
      AddSorted(&coll->npRight, coll->fMedian, Ascending);      
    }
    
    //calculate new median
    coll->fMedian = (coll->npLeft->item + coll->npRight->item)/2.0;
  }
  else //even to odd
  {
    //cout<<"[even to odd]"<<endl;    
    coll->cnt++;
    if(value > coll->fMedian)
    {
      coll->fMedian = coll->npRight->item;
      PullFirst(&coll->npRight);
      AddSorted(&coll->npRight, value, Ascending);
    }
    else
    {
      coll->fMedian = coll->npLeft->item;
      PullFirst(&coll->npLeft);
      AddSorted(&coll->npLeft, value, Descending);    
    }
  }  
  
  //cout<<"[Insert] first left item is "<<coll->npLeft->item<<endl;
  //cout<<"[Insert] first right item is "<<coll->npRight->item<<endl;
  return coll->fMedian;
}




int main() {
  float value;
  MEDIAN_COLLECTION coll;
  coll.cnt = 0;
  coll.npLeft = NULL;
  coll.npRight = NULL;
    
  value = 1;
  cout << "After inserting "<<value<<", median is "<<Insert(&coll, value)<<endl;
  value = 2;
  cout << "After inserting "<<value<<", median is "<<Insert(&coll, value)<<endl;
  value = 8;
  cout << "After inserting "<<value<<", median is "<<Insert(&coll, value)<<endl;
  value = -1;
  cout << "After inserting "<<value<<", median is "<<Insert(&coll, value)<<endl;  
  value = -6;
  cout << "After inserting "<<value<<", median is "<<Insert(&coll, value)<<endl;  
  value = 0;
  cout << "After inserting "<<value<<", median is "<<Insert(&coll, value)<<endl;
  value = 3;
  cout << "After inserting "<<value<<", median is "<<Insert(&coll, value)<<endl;  
  value = 5;
  cout << "After inserting "<<value<<", median is "<<Insert(&coll, value)<<endl;  
  
  return 0;
}