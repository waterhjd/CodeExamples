#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <iostream>

#include <sys/time.h>
#include <unistd.h>

#define MINIMUMCOUNT 4
#define MAXIMUMCOUNT 20

#define PRINTLIST 0
#if PRINTLIST
void PrintList( const unsigned int *list, unsigned int listLen );
#endif 

#define TEST_INSERTION_SORT 1
#if TEST_INSERTION_SORT
#include "insertionsort.h"
void TestInsertionSort( const unsigned int *list, unsigned int listLen );
#endif // TEST_INSERTION_SORT

#define TEST_MERGE_SORT 1
#if TEST_MERGE_SORT
#include "mergesort.h"
void TestMergeSort( const unsigned int *list, unsigned int listLen );
#endif // TEST_MERGE_SORT

#define TEST_RADIX_SORT 1
#if TEST_RADIX_SORT
#include "radixsort.h"
void TestRadixSort( const unsigned int *list, unsigned int listLen );
#endif // TEST_RADIX_SORT

#define TEST_HEAP_SORT 1
#if TEST_HEAP_SORT
#include "heapsort.h"
void TestHeapSort( const unsigned int *list, unsigned int listLen );
#endif // TEST_HEAP_SORT

struct timeval profileStart, profileEnd;

int main( int argc, char **argv )
{
	for( unsigned int i = MINIMUMCOUNT; i < MAXIMUMCOUNT; i++ )
	{
		int numEntries = 1 << i;
		unsigned int *unsortedList = new unsigned int[ numEntries ];
		// Get deterministic pseudo-random numbers to perform the sort on
		{
			unsortedList[0] = 37;
			for( int r = 1; r < numEntries; r++ )
			{
				int prevVal = unsortedList[r-1];
				unsortedList[r] = (prevVal >> 1) ^ (-(prevVal & 1u) & 0xD0000001u);
				unsortedList[r] = (unsortedList[r] % 15877);
			}
		}

		std::cout << "Num Entries: " << numEntries << std::endl;
		#if PRINTLIST
		PrintList( unsortedList, numEntries );
		#endif // PRINTLIST

		#if TEST_INSERTION_SORT
		std::cout << "**************  Testing Insertion Sort  ***************" << std::endl << std::endl;
		TestInsertionSort( unsortedList, numEntries );
		std::cout << "************  Done Testing Insertion Sort ************" << std::endl << std::endl;
		#endif // TEST_INSERTION_SORT

		#if TEST_MERGE_SORT
		std::cout << "**************  Testing Merge Sort  ***************" << std::endl << std::endl;
		TestMergeSort( unsortedList, numEntries );
		std::cout << "************  Done Testing Merge Sort ************" << std::endl << std::endl;
		#endif // TEST_MERGE_SORT

		#if TEST_RADIX_SORT
		std::cout << "**************  Testing Radix Sort  ***************" << std::endl << std::endl;
		TestRadixSort( unsortedList, numEntries );
		std::cout << "************  Done Testing Radix Sort ************" << std::endl << std::endl;
		#endif // TEST_RADIX_SORT

		#if TEST_HEAP_SORT
		std::cout << "**************  Testing Heap Sort  ***************" << std::endl << std::endl;
      TestHeapSort( unsortedList, numEntries );
		std::cout << "************  Done Testing Heap Sort ************" << std::endl << std::endl;
		#endif // TEST_HEAP_SORT

		delete [] unsortedList;
	}

	return 0;
}

#if PRINTLIST
void PrintList( const unsigned int *list, unsigned int listLen )
{
	for( unsigned int i = 0; i < listLen; i++ )
	{
		std::cout << list[i];
		if( i < (listLen-1) ) std::cout << ", ";
	}

	std::cout << std::endl;
}
#endif // PRINTLIST

void PrintTimeDifference( const timeval &start, const timeval &end )
{
	long mtime, seconds, useconds; 
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;

	mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

	std::cout << "Elapsed time: " << mtime << " milliseconds" << std::endl;
}

#if TEST_INSERTION_SORT

void TestInsertionSort( const unsigned int *origList, unsigned int listLen ) 
{
	unsigned int *list = new unsigned int[ listLen ];
	memcpy( list, origList, sizeof( unsigned int ) * listLen );

	gettimeofday( &profileStart, NULL );
	// Perform sort here
	insertionsort( list, listLen );
	gettimeofday( &profileEnd, NULL );
	PrintTimeDifference( profileStart, profileEnd );

	#if PRINTLIST
	PrintList( list, listLen );
	#endif 
}

#endif // TEST_INSERTION_SORT

#if TEST_MERGE_SORT

void TestMergeSort( const unsigned int *origList, unsigned int listLen ) 
{
	unsigned int *list = new unsigned int[ listLen ];
	memcpy( list, origList, sizeof( unsigned int ) * listLen );

    unsigned int *tempBuffer = new unsigned int[ listLen ];
    memset( tempBuffer, 0, sizeof( int ) * listLen );

	gettimeofday( &profileStart, NULL );
	// Perform sort here
	mergesort( list, listLen, tempBuffer );
	gettimeofday( &profileEnd, NULL );
	PrintTimeDifference( profileStart, profileEnd );

	#if PRINTLIST
	PrintList( list, listLen );
	#endif 
}

#endif // TEST_MERGE_SORT

#if TEST_RADIX_SORT

void TestRadixSort( const unsigned int *origList, unsigned int listLen ) 
{
	unsigned int *list = new unsigned int[ listLen ];
	memcpy( list, origList, sizeof( unsigned int ) * listLen );

    unsigned int *tempBuffer = new unsigned int[ listLen ];
    memset( tempBuffer, 0, sizeof( int ) * listLen );

	gettimeofday( &profileStart, NULL );
	// Perform sort here
	radixsort( list, listLen, tempBuffer );
	gettimeofday( &profileEnd, NULL );
	PrintTimeDifference( profileStart, profileEnd );

	#if PRINTLIST
	PrintList( list, listLen );
	#endif 
}

#endif // TEST_RADIX_SORT

#if TEST_HEAP_SORT

void TestHeapSort( const unsigned int *origList, unsigned int listLen ) 
{
	unsigned int *list = new unsigned int[ listLen ];
	memcpy( list, origList, sizeof( unsigned int ) * listLen );

    unsigned int *tempBuffer = new unsigned int[ listLen ];
    memset( tempBuffer, 0, sizeof( int ) * listLen );

	gettimeofday( &profileStart, NULL );
	// Perform sort here
	heapsort( list, listLen, tempBuffer );
	gettimeofday( &profileEnd, NULL );
	PrintTimeDifference( profileStart, profileEnd );

	#if PRINTLIST
	PrintList( list, listLen );
	#endif 
}

#endif // TEST_HEAP_SORT
