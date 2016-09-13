#include "insertionsort.h"

void insertionsort( unsigned int *list, unsigned int listLen )

{
   for( unsigned int i = 1; i < listLen; i++)
   {
      int j = i;
      while (j > 0 && list[j - 1] > list[j])
      {
         int temp = list[j];
	      list[j] = list[j-1];
	      list[j-1] = temp;
         j--;
      }
   }
}


