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


typedef struct Coord_ts
{
  int i;
  int j;
} COORD;


typedef struct Node_ts
{
  COORD item;
  struct Node_ts *next;
  struct Node_ts *prev;
} NODE, *NODE_PTR, **NODE_PTR_PTR;


void Enqueue(NODE_PTR_PTR head, COORD item)
{
  if(NULL == *head)
  {
    *head = (NODE_PTR) malloc(sizeof(NODE));
    (*head)->item.i = item.i;
    (*head)->item.j = item.j;
    (*head)->next = NULL;
    (*head)->prev = NULL;
  }
  else
  {
    NODE_PTR node = (NODE_PTR) malloc(sizeof(NODE));
    node->item.i = item.i;
    node->item.j = item.j;
    (*head)->prev = node;
    node->next = *head;
    node->prev = NULL;
    *head = node;
  }
}


COORD Dequeue(NODE_PTR_PTR head)
{
  NODE_PTR iter = *head;
  COORD item;
  while(NULL != iter->next)
  {
    iter = iter->next;
  }
  
  //copy value
  item.i = iter->item.i;
  item.j = iter->item.j;
  //remove the item from the queue
  if(NULL == iter->prev)
  {
    //last node remaining
    delete iter;
    iter = NULL;
    *head = NULL;
  }
  else
  {
    iter->prev->next = NULL;
    delete iter;
  }
  
  return item;
}


#define SEA 0
#define LAND 1


int main() {
  
  int matrix[][5] = { 
    {SEA, LAND, LAND, SEA, LAND},
    {LAND, LAND, LAND, SEA, SEA},
    {LAND, LAND, LAND, SEA, SEA},
    {SEA, SEA, SEA, LAND, LAND},
    {LAND, SEA, SEA, LAND, SEA}
  };
  COORD item;
  NODE_PTR queue = NULL;
  int cnt = 0;
  
  for(int i=0; i<5; i++)
  {
    for(int j=0; j<5; j++)
    {
      if(LAND == matrix[i][j])
      {
        cnt++;
        cout<<"Found island "<<cnt<<"\n";
        matrix[i][j] = SEA;
        item.i = i;
        item.j = j;
        Enqueue(&queue, item);
        cout<<"Item ("<<item.i<<","<<item.j<<") added"<<"\n";
        while(NULL != queue)//while queue not empty
        {
          item = Dequeue(&queue);
          cout<<"Item ("<<item.i<<","<<item.j<<") removed"<<"\n";
          for(int k=item.i-1; k<=item.i+1; k++)
          {
            for(int l=item.j-1; l<=item.j+1; l++)
            {
              if(k>=0 && k<5 && l>=0 && l<5)
              {
                if(LAND==matrix[k][l])
                {
                  matrix[k][l] = SEA;
                  item.i = k;
                  item.j = l;
                  Enqueue(&queue, item);
                  cout<<"Item ("<<item.i<<","<<item.j<<") added"<<"\n";
                }                
              }
            }
          }
        }
      }
    }
  }
  
  cout<<cnt;
  
  return 0;
}