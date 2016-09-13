#include "mergesort.h"
#include <iostream>

using namespace std;

void mergesort( unsigned int *list, unsigned int listLen, unsigned int *tempbuffer )
{
  if(listLen > 1)
  {
   mergesort(list, listLen/2,tempbuffer);
   unsigned int Upper = (listLen - listLen/2);
   mergesort(&list[Upper], Upper, tempbuffer);

   unsigned int Lower = 0;
   unsigned int Mid = Upper;
   
   for (unsigned int i = 0; i < listLen; i++)
   {
      if(Lower < Upper)
      {
         if(Mid < listLen)
         {
            if( list[Lower] < list[Mid])
            {
               tempbuffer[i] = list[Lower];
               Lower++;
            }
            else
            {
               tempbuffer[i] = list[Mid];
               Mid++;
            }
         }
         else
         {
            tempbuffer[i] = list[Lower];
            Lower++;
         }
      }   
      else
      {
         tempbuffer[i] = list[Mid];
         Mid++;
      }
   }
   for (unsigned int i = 0; i < listLen; i++)
   {
      list[i] = tempbuffer[i];
   }
   } else {
      return;
   }
}
