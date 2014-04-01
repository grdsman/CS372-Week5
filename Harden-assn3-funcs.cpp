#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "CoppockHarden-assn3-common.h"
#include "Coppock-assn3-funcs.h"
#include "Harden-assn3-funcs.h"

// *************************************************************************************
// FUNCTION:	LoadDoubleHashArray
// DESCRIPTION:	Takes an itialized array and loads it with hashed integers from the random
//				integer array using modulo division.  If a collision occurs, calls a 
//				separate function to perform a double hash algorithm to resolve 
//				the collision.
// INPUT:		Parameters:	doubleHashArray - array to hash integers into
//							randomArray - array containing random integers
//							size - int holding the hash table size
// OUTPUT:		Parameters: doubleHashArray - array with hashed integers loaded
//				Return val: found - bool variable indicating whether double hash was 
//									successful (no infinite loop)
// CALLS TO:	UseModuloDiv, DoubleHash
// IMPLMENTED BY: Keith Harden
// *************************************************************************************
bool LoadDoubleHashArray(int doubleHashArray[], int randomArray[], int size)
{
    int i = 0,
        address;
    bool found = true;
    
    
    while((i < MAX) && found)
    {
        address = UseModuloDiv(randomArray[i], size);
        if(doubleHashArray[address] == EMPTY_ADDRESS)
            doubleHashArray[address] = randomArray[i];
        else
        {
            found = DoubleHash(doubleHashArray, randomArray[i], address, size);
            if(found)
				doubleHashArray[address] = randomArray[i];
        }
       i++;
    }
     
   return found;
}

// *************************************************************************************
// FUNCTION:	DoubleHash
// DESCRIPTION:	Attemps to resolve hash collision that may occur while hashing random
//				integers into an array using a double hash algorithm. Loops until it 
//				is able to place the integer into a cell of the array or exits with
//				an error message if an infinite loop occurs.
// INPUT:		Parameters:	doubleHashArray - array to hash integers into
//							key - integer to be hashed into array
//							address - variable to hold address location in array
//							size - int holding the hash table size
// OUTPUT:		Parameters: address - variable to hold address location in array
//				Return val: found - bool variable indicating whether double hash was 
//									successful (no infinite loop)
// CALLS TO:	N/A
// IMPLMENTED BY: Keith Harden
// *************************************************************************************
bool DoubleHash(int doubleHashArray[], int key, int& address, int size)
{
    bool found = false;
	int count = 0;
	int secondHash = 0;
    
    secondHash = (key % (size - DOUBLE_HASH_MOD)) + DOUBLE_HASH_CONSTANT;
    
    do
    {
		address = UseModuloDiv((address + secondHash), size);
		    
        if(doubleHashArray[address] == EMPTY_ADDRESS)
        {
            found = true;
        }
				
        count++;
        
    }while(!found && count <= size);
        
        
    return found; 
}

// *************************************************************************************
// FUNCTION:	GetLoadFactor
// DESCRIPTION:	Calculates the load factor of the hash table by performing load 
//				factor calculation.
// INPUT:		Parameters:	size - int holding the hash table size
// OUTPUT:		Parameters: N/A
//				Return val: loadFactor - load factor of hash table
// CALLS TO:	N/A
// IMPLMENTED BY: Keith Harden
// *************************************************************************************
float GetLoadFactor(int size)
{
	float loadFactor;
	float tableSize = size;
	
	loadFactor = MAX / tableSize;
	
	return loadFactor;
}

// *************************************************************************************
// FUNCTION:	HashAnalysis
// DESCRIPTION:	Calls functions to perform hash analysis of different collision methods
//				 and to print results. 
// INPUT:		Parameters:	doubleHashSuccess - bool indicating if double was successful
//							hashArray - linear array to be searched
//							doubleHashArray - double hashed array to be searched
//							chainedHashArray - chained hased array to be searched
//							randomArray - array containing random integers
//							size - int holding the hash table size
//							evenOrOdd - integer representing even or odd to
//                                      provide a starting place to search
//							loadFactor - load factor of hash tables
// OUTPUT:		Parameters: N/A
// 				Return val: N/A
// CALLS TO:	SearchLinearHash, SearchDoubleHash, SearchChainedHash, GetKnuthAverage, 
//              PrintResults
// IMPLMENTED BY: Keith Harden
// *************************************************************************************
void HashAnalysis(bool doubleHashSuccess, int hashArray[], int doubleHashArray[], 
node* chainedHashArray[], int randomArray[], int size, int evenOrOdd, float loadFactor)
{
	int linearItemsSearched = 0;
	int doubleItemsSearched = 0;
	int chainedItemsSearched = 0;
	float linearAverage = 0;
	float doubleAverage = 0;
	float chainedAverage = 0;
	float linearKnuthAverage = 0;
	float doubleKnuthAverage = 0;
	float chainedKnuthAverage = 0;
	
	SearchLinearHash(hashArray, randomArray, size, evenOrOdd, linearItemsSearched, linearAverage);
		
	if(doubleHashSuccess)
		SearchDoubleHash(doubleHashArray, randomArray, size, evenOrOdd, doubleItemsSearched, doubleAverage);
		
	SearchChainedHash(chainedHashArray, randomArray, size, evenOrOdd, chainedItemsSearched, chainedAverage);
	
	GetKnuthAverage(loadFactor, linearKnuthAverage, doubleKnuthAverage, chainedKnuthAverage);
	
	PrintResults(doubleHashSuccess, size, linearItemsSearched, doubleItemsSearched, chainedItemsSearched,
	 linearAverage, doubleAverage, chainedAverage, loadFactor, linearKnuthAverage, doubleKnuthAverage, 
	  chainedKnuthAverage);
}

// *************************************************************************************
// FUNCTION:	SearchDoubleHash
// DESCRIPTION:	Searches array for half of the integers in the random integer array
//				based on a choice from user to search in even or odd cells.  
//				Keeps track of how many elements in the need to be examined in the 
//				array for each search and calculates an average number of items
//				searched per search.
// INPUT:		Parameters:	doubleHashArray - array to be searched
//							randomArray - array containing random integers
//							size - int holding the hash table size
//							evenOrOdd - integer representing even or odd to
//                                      provide a starting place to search
//							items - int holding number of items examined
//							average - average number of items examiner per search
// OUTPUT:		Parameters: items - int holding number of items examined
//							average - average number of items examined per search
//				Return val: N/A
// CALLS TO:	UseModuloDiv
// IMPLMENTED BY: Keith Harden
// *************************************************************************************
void SearchDoubleHash(int doubleHashArray[], int randomArray[], int size, int evenOrOdd, int& items, float& average)
{
	 int i = 0,
         address = 0,
         secondHash = 0;
     bool found = false;
     float foundCount = 0;
     
     
     average = 0;
     
     i = evenOrOdd;
     
     
     while(i < MAX)
     {
         found = false;
         address = UseModuloDiv(randomArray[i], size);
         
         while(!found)
         {
             if(randomArray[i] == doubleHashArray[address])
             {
                 found = true;
                 items++;
                 foundCount++;
             }
             else
             {
                 items++;
                 secondHash = (randomArray[i] % (size - DOUBLE_HASH_MOD)) + DOUBLE_HASH_CONSTANT;
                 address = UseModuloDiv((address + secondHash), size);
             }
         }
             
         i = i + 2;
     }
     
     average = items / foundCount;
}

	
// *************************************************************************************
// FUNCTION:	GetKnuthAverage
// DESCRIPTION:	Calculates the Knuth average for number of elements searched based
//				on the load factor and the type of collision resolution used.
// INPUT:		Parameters:	loadFactor - load factor of hash table
//							linearKnuthAverage - knuth average for linear probing
//							doubleKnuthAverage - knuth average for double hashing
//							chainedKnuthAverage - knuth average for chained hashing
// OUTPUT:		Parameters: linearKnuthAverage - knuth average for linear probing
//							doubleKnuthAverage - knuth average for double hashing
//							chainedKnuthAverage - knuth average for chained hashing
//				Return val: N/A
// CALLS TO:	N/A
// IMPLMENTED BY: Keith Harden
// *************************************************************************************
void GetKnuthAverage(float loadFactor, float& linearKnuthAverage, float& doubleKnuthAverage, float& chainedKnuthAverage)
{	
		linearKnuthAverage = KNUTH_LINEAR * (KNUTH_CONSTANT + (KNUTH_CONSTANT / 
		(KNUTH_CONSTANT - loadFactor)));
	
		doubleKnuthAverage = -log(KNUTH_CONSTANT - loadFactor) / loadFactor;
			
		chainedKnuthAverage = KNUTH_CONSTANT + (loadFactor / KNUTH_DIVISION);
}
	
// *************************************************************************************
// FUNCTION:	PrintResults
// DESCRIPTION:	Prints the results of previous hash table search, including the load 
//				factor, type of collision used to load hash table, number of items
//				examined, and the average number of items examined per search. 
//				It then compares the average to the Knuth predicted average.
// INPUT:		Parameters:	doubleHashSuccess - bool indicating if double hashing 
//											resulted in infinite loop
//							size - int holding the hash table size
//							linearItemsSearched - int holding number of items examined for linear probing
//							DoubleItemsSearched - int holding number of items examined for double hashing
//							chainedItemsSearched - int holding number of items examined for chained hashing
//							linearAverage - average number of items examined per search for linear probing
//							doubleAverage - average number of items examined per search for double hashing
//							chainedAverage - average number of items examined per search for chained hashing
//							loadFactor - load factor of hash table
//							linearKnuthAverage - double holding Knuth average for linear probing
//							doubleKnuthAverage - double holding Knuth average for double hashing
//							chainedKnuthAverage - double holding Knuth average for chained hashing
// OUTPUT:		Parameters: N/A
//				Return val: N/A
// CALLS TO:	N/A
// IMPLMENTED BY: Keith Harden
// *************************************************************************************
void PrintResults(bool doubleHashSuccess, int size, int linearItemsSearched, int doubleItemsSearched, 
	 int chainedItemsSearched, float linearAverage, float doubleAverage, float chainedAverage, 
	  float loadFactor, float linearKnuthAverage, float doubleKnuthAverage, float chainedKnuthAverage)
{
	cout << fixed << setprecision(3);
	cout << endl << MAX << " items loaded into a " << size << " element hash table" << endl;
	cout << "Load Factor = " << loadFactor << endl << endl;
	cout << "Results of searching for 2500 items:" << endl << endl;
	
	
	cout << setw(19) << "Linear Probing" << endl;
	cout << setw(12) << linearItemsSearched << " items examined (avg = " << linearAverage << 
		" items examined per search)" << endl;
	cout << setw(35) << "vs Knuth predicted avg = " << linearKnuthAverage <<
		" items examined per search" << endl << endl;
	
	cout << setw(19) << "Double Hashing" << endl;
	if(!doubleHashSuccess)
		cout << setw(73) << "No results to display.  Double hashing resulted in infinite loop." << endl << endl;
	
	else
	{
		cout << setw(12) << doubleItemsSearched << " items examined (avg = " << doubleAverage << 
			" items examined per search)" << endl;
		cout << setw(35) << "vs Knuth predicted avg = " << doubleKnuthAverage <<
			" items examined per search" << endl << endl;
	}
	
	cout << setw(20) << "Chained Hashing" << endl;
	cout << setw(12) << chainedItemsSearched << " items examined (avg = " << chainedAverage << 
		" items examined per search)" << endl;
	cout << setw(35) << "vs Knuth predicted avg = " << chainedKnuthAverage <<
		" items examined per search" << endl << endl;
}
