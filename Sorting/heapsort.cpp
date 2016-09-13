#include "heapsort.h" 
#include "sortutilities.h"


void heapsort( unsigned int *list, unsigned int listLen, unsigned int *tempbuffer )
{
   //Heapify The List
   for(unsigned int i = 0; i < listLen; i++)
   {
      unsigned int current = i;
      unsigned int parent = (current/2);      
      tempbuffer[i] = list[i];
      bool sorted = false; 
      // if i = 0 there is only one node so there is no balancing needed
      if (i != 0)
      {
         //While not sorted as a heap
         while(!sorted)
         {
            if((tempbuffer[current] > tempbuffer[parent])&&(current != 0))
            {
               //If it is a left node
               if ((current%2) == 1)
               {
                  swap(tempbuffer[current], tempbuffer[parent]);
                  current = parent;
               // If it is a right node
               } else {
                  swap(tempbuffer[current], tempbuffer[parent-1]);
                  current = parent-1;
               }
               // Bubble up the heap
               parent = current/2;
            } else {
               sorted = true;
            }
         }
      }
   }

   //Remove items from the root 
   unsigned int buffLen = listLen;
   for (unsigned int i = 0; i < listLen; i++)
   {
      // Put largest thing into list
      list[listLen-i-1] = tempbuffer[0];

      // Get rid of the Largest thing
      tempbuffer[0]=tempbuffer[buffLen-1];
      buffLen--;
      
      // Re-Sort the heap
      unsigned int left = 1;
      unsigned int right = 2;
      unsigned int current = 0;
      bool sorted = false; 
      
      while ((!sorted)&&(buffLen > 1))
      {
         // Checks if it needs to be sorted
         if ((tempbuffer[left] > tempbuffer[current])||(tempbuffer[right] > tempbuffer[current]))
         {
            // If the Left side is the largest it should become the new parent
            if(tempbuffer[left] > tempbuffer[right])
            {
               swap(tempbuffer[left], tempbuffer[current]);
               current = left;
            } else {
               swap(tempbuffer[right], tempbuffer[current]);
               current = right;
            }  
            left = (current*2)+1;
            right = (current*2)+2;
         } else sorted = true;
         
         if ((left > buffLen)&&(right > buffLen))
         {
            sorted = true;

         }
         else 
         {
            if(left > buffLen)
            {
               left = current; 
            }
            else if(right > buffLen)
            {
               right = current; 
            }
         }
      }   
   }
}
