#include "radixsort.h"

void radixsort( unsigned int *list, unsigned int listLen, unsigned int *tempbuffer )
{
   // Array to hold N and Accumulator
   unsigned int radix[10][2];

   int foo = 1;
   bool sorted = false;
   while(!sorted)
   {
      //Set up temp buffer
      for (unsigned int i = 0; i < listLen; i++)
      {
         tempbuffer[i] = list[i];
      }
      // Initialize list
      for (unsigned int i = 0; i < 10; i++)
      {
         radix[i][0] = 0;
         radix[i][1] = 0;
      }
      unsigned int count = 0;
      // Sort array into Bucket
      for (unsigned int i = 0; i < listLen; i++)
      {
         if (((int)tempbuffer[i]/foo) == 0)
         {
            count++;
            if (count == listLen)
               sorted = true;
         }
         radix[(((int)tempbuffer[i]/foo)%10)][0]++;
      }

      // Set Up the Accumulator
      unsigned int nPrev = 0;
      for (unsigned int i = 0; i < 10; i++)
      {
         radix[i][1] = nPrev;
         nPrev += radix[i][0];
      }

      // Copy Temp Buffer into list
      for (unsigned int i = 0; i < listLen; i++)
      {
         list[radix[(((int)tempbuffer[i]/foo)%10)][1]] = tempbuffer[i];
         radix[(((int)tempbuffer[i]/foo)%10)][1]++;
      }

      // Move to next Place Value
      foo *= 10;
   
   }
}
