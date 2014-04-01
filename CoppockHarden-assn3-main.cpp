//******************************************************************************
// CODE FILENAME: CoppockHarden-assn3-main.cpp
// DESCRIPTION: This program performs searching operations of hash tables
//				by loading an array with random numbers and then populating
//				hash tables with the values, stored at hashed addresses.  When
//				the hash tables are complete, the searching functions will go
//				back through the random number array to find even or odd numbers
//				in the hash tables, comparing their search results to Knuth's 
//				averages.
// CLASS/TERM: CS372/Spring 2014 8W2
// DESIGNER: Coppock, Michael and Harden, Keith
// FUNCTIONS: IsDup - checks whether a value is a duplicate in an array of integers
//			  CreateRandomList - generates random numbers and inserts them into an array
//			  GetInput - requests input from the user for the hash table size
//			  GetEvenOrOdd - requests input from the user as to whether they would like
//							to search for even or odd members of the random array
//			  IsValidInput - validates the input hash table size
//			  InitializeArray - initializes an array of integers
//			  LoadLinearHashArray - loads integers into a hash table array
//			  UseModuloDiv - calculates the initial hash using modulo division
//			  LinearProbe - searches the array for an available location when a
//							collision occurs
//			  InitializeChainedArray - initializes an array of pointers
//			  LoadChainedArray - gets the hashed address for the random integer and
//								 calls the AddNode function to load it
//			  AddNode - loads the chained array with new nodes
//			  SearchLinearHash - searches the linear hash table for numbers in the
//								 random integer array
//			  SearchChainedHash - searches the chained hash table for number from
//								  the random integer array
//			  DestroyList - destroys a list given a list top pointer
//			  DestroyChainedArray - finds array locations that have a valid pointer
//									and calls the DestroyList function to destroy it
//			  LoadDoubleHashArray - loads the double hash array table with integers
//									in hashed address locations
//			  DoubleHash - calculates the double hash address
//			  GetLoadFactor - calculates the load factor
//			  HashAnalysis - calls other search functions and gathers data about the
//							 search results
//			  SearchDoubleHash - searches the double hash table for integers from
//								 the random integer array
//			  GetKnuthAverage - calculates the Knuth average for a given load factor
//								and type of hash being used
//			  PrintResults - displays the results of the searches to the screen
//****************************************************************************** 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "CoppockHarden-assn3-common.h"
#include "Coppock-assn3-funcs.h"
#include "Harden-assn3-funcs.h"

// ******************************************************************************
// FUNCTION:	main
// DESCRIPTION:	Designates variables and calls various functions.  Exits with exit 
// 				code zero.
// CALLS TO:	InitializeArray, CreateRandomList, GetInput, LoadLinearHashArray,
//				LoadDoubleHashArray, InitializeChainedArray, LoadChainedArray,
//				GetEvenOrOdd, GetLoadFactor, HashAnalysis
// ******************************************************************************
int main()
{
    int size = 0,
        evenOrOdd;
    float loadFactor;
    bool doubleHashSuccess;
    
    int randomArray[MAX];
    InitializeArray(randomArray, MAX);
    CreateRandomList(randomArray);
        
    size = GetInput();
    
    int linearHashArray[size];
    InitializeArray(linearHashArray, size);
    LoadLinearHashArray(linearHashArray, randomArray, size);
    
    int doubleHashArray[size];
	InitializeArray(doubleHashArray, size);
    doubleHashSuccess = LoadDoubleHashArray(doubleHashArray, randomArray, size);
    
    node *chainedHashArray[size];
    InitializeChainedArray(chainedHashArray, size);
    LoadChainedArray(chainedHashArray, randomArray, size);
    
    evenOrOdd = GetEvenOrOdd();
    
    loadFactor = GetLoadFactor(size);
    
    HashAnalysis(doubleHashSuccess, linearHashArray, doubleHashArray, chainedHashArray, 
	randomArray, size, evenOrOdd, loadFactor);
	
	DestroyChainedArray(chainedHashArray, size);
    
    system("pause");

    return 0;
}
