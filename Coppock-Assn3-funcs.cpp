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
// FUNCTION:	IsDup
// DESCRIPTION:	Takes an input of an integer, an array and a count and searches
//              the array in order to determine whether a number is a duplicate
//              or not
// INPUT:		Parameters:	randomArray - array to load random integers into
//							count - int holding the number of members in the array
//                                  currently
//                          randomNum - the integer to search for
// OUTPUT:		Parameters: N/A
//              Return: dup - boolean value of whether it was found or not
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
bool IsDup(int randomNum, int randomArray[], int count)
{
   bool dup = false;
   int i;
   
   for(i = 0; i < count; i++)
   {
       if(randomArray[i] == randomNum)
       {
           dup = true;
           
       }
   }
   
   return dup;
}


// *************************************************************************************
// FUNCTION:	CreateRandomList
// DESCRIPTION:	Takes an itialized array and loads it with random integers.
// INPUT:		Parameters:	randomArray - array to load random integers into
// OUTPUT:		Parameters: randomArray - array with random integers loaded
// CALLS TO:	IsDup - function for searching the array for existing integers
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
void CreateRandomList(int randomArray[])
{
    int i,
        randomNum,
        count = 0;
    
    for(i = 0; i < MAX; i++)
    {
          randomNum = rand() % RANDOM_NUM + 1;
          
          if(!IsDup(randomNum, randomArray, count))
          {
              randomArray[i] = randomNum;
               count++;
          }
          else
          i--;
    }
}

// *************************************************************************************
// FUNCTION:	GetInput
// DESCRIPTION:	Gets input from the user as to the desired size for the hash table
// INPUT:		Parameters:	N/A
// OUTPUT:		Parameters: N/A
//              Return val: size - the input size of the hash table
// CALLS TO:	IsValidInput - validates the user input
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
int GetInput()
{
    int size = 0;
    
    do
    {
                  
        cout << "Please enter a size for the hash table: " << endl;
        cin >> size;
    }while(!IsValidInput(size));
    
    return size;
}

// *************************************************************************************
// FUNCTION:	IsValidInput
// DESCRIPTION:	validates the user input value
// INPUT:		Parameters:	size - user input integer value to validate
// OUTPUT:		Parameters: N/A
//              Return val: size - the input size of the hash table
// CALLS TO:	IsValidInput - validates the user input
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
bool IsValidInput(int size)
{
    bool isValid = true;

    if(size < MIN)
        isValid = false;
            
    if(isValid == false)
        cout << "The hash table size you input is invalid." << endl << endl;
    
    return isValid;
        
}

// *************************************************************************************
// FUNCTION:	InitializeArray
// DESCRIPTION:	Initializes an array of integers
// INPUT:		Parameters:	someArray - an array of type integer
//                          size - the size of the array
// OUTPUT:		Parameters: someArray - an array of type integer with cells initialized
//              Return val: N/A
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
void InitializeArray(int someArray[], int size)
{
     int i;
     
     for(i = 0; i < size; i++)
     {
         someArray[i] = EMPTY_ADDRESS;
     }
     
}

// *************************************************************************************
// FUNCTION:	InitializeChainedArray
// DESCRIPTION:	Initializes an array of pointers
// INPUT:		Parameters:	someArray - an array of pointers
//                          size - the size of the array
// OUTPUT:		Parameters: someArray - an initialized array of pointers
//              Return val: N/A
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************     
void InitializeChainedArray(node* someArray[], int size)
{
     int i;
     
     for(i = 0; i < size; i++)
     {
         someArray[i] = NULL;
     }
     
}     

// *************************************************************************************
// FUNCTION:	UseModuloDiv
// DESCRIPTION:	Calculates the initial hash using modulo division
// INPUT:		Parameters:	key - the key to hash
//                          modulo - the number to use in the modulo division formula
// OUTPUT:		Parameters: N/A
//              Return val: address - the hashed address for the key to be stored in
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
int UseModuloDiv(int key, int modulo)
{
     int address;
     
     address = key % modulo;
     
     return address;
}

// *************************************************************************************
// FUNCTION:	LoadLinearHashArray
// DESCRIPTION:	Loads the linearHashArray with integers based on the hash value as the
//              address.  If the address location is already populated, it will call
//              the LinearProbe function to find a secondary address.
// INPUT:		Parameters:	linearHashArray - array of integers, stored by hashed address
//                          randomArray - array of random integers
//                          size - the size of the hash table
// OUTPUT:		Parameters: linearHashArray - array of integers, stored by hashed address
//              Return val: N/A
// CALLS TO:	UseModuloDiv - function for calculating the initial address location
//              LinearProbe - function for finding an available address location if
//                            the primary address was not available
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
void LoadLinearHashArray(int linearHashArray[], int randomArray[], int size)
{
    int i,
        address;
    
    
    for(i = 0; i < MAX; i++)
    {
        address = UseModuloDiv(randomArray[i], size);
        
        if(linearHashArray[address] == EMPTY_ADDRESS)
            linearHashArray[address] = randomArray[i];
        else
        {
            address = LinearProbe(linearHashArray, address, size);
            linearHashArray[address] = randomArray[i];
        }
    }
     
}

// *************************************************************************************
// FUNCTION:	LinearProbe
// DESCRIPTION:	Finds an available address location when the primary location was
//              not available by searching sequentially through the list, starting
//              at the original address location
// INPUT:		Parameters:	linearHashArray - array of integers, stored by hashed address
//                          address - the original address location for an integer
// OUTPUT:		Parameters: N/A
//              Return val: i - the new address location
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
int LinearProbe(int linearHashArray[], int address, int size)
{
    int i = 0;
    bool found = false;
    
    i = address;
    
    do
    {
        if(linearHashArray[i] == EMPTY_ADDRESS)
            found = true;
        else if(i >= size)
       	    i = 0;
       	else
            i++;
    }while(!found);
         
    return i; 
     
}


// *************************************************************************************
// FUNCTION:	LoadChainedArray
// DESCRIPTION:	Loads the chainedHashArray pointers to the top node of a linked
//              list of integers.
// INPUT:		Parameters:	chainedHashArray - array of pointers to linked lists
//                          of integers.
//                          randomArray - array of random integers
//                          size - the size of the hash table
// OUTPUT:		Parameters: chainedHashArray - array of pointers to linked lists
//                          of integers.
//              Return val: N/A
// CALLS TO:	UseModuloDiv - function for calculating the initial address location
//              AddNode - adds a node to a linked list
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
void LoadChainedArray(node* chainedHashArray[], int randomArray[], int size)
{
    int i,
        address;
    
    for(i = 0; i < MAX; i++)
    {
        address = UseModuloDiv(randomArray[i], size);
        AddNode(chainedHashArray, address, randomArray[i]);
    }

}

// *************************************************************************************
// FUNCTION:	AddNode
// DESCRIPTION:	Adds a node to the chainedHashArray, which is an array of pointers
//              to linked lists.
// INPUT:		Parameters:	chainedHashArray - array of pointers to linked lists
//                          of integers.
//                          address - the hashed address for where to place
//                                    the node in the array.
//                          number - the integer value to place in the node
// OUTPUT:		Parameters: chainedHashArray - array of pointers to linked lists
//                          of integers.
//              Return val: N/A
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
void AddNode(node* chainedHashArray[], int address, int number)
{
     node* newNode = new node;
     
     if (newNode == NULL)
     {
         cout << "Heap error - could not allocate memory" << endl;
     }
     
     else
     {
         newNode->num = number;
         newNode->next = NULL;
         
         //array location will be NULL if no list exists yet
         if(chainedHashArray[address] == NULL)
         {
             chainedHashArray[address] = newNode;
             
         }
         else
         {
             newNode->next = chainedHashArray[address];
             chainedHashArray[address] = newNode;
         }
     }
}

// *************************************************************************************
// FUNCTION:	GetEvenOrOdd
// DESCRIPTION:	Requests user input for whether they want to search the even or
//              odd members of an array
// INPUT:		Parameters:	N/A
// OUTPUT:		Parameters: N/A
//              Return val: evenOrOdd - an integer to be used to represent even or odd (0 or 1)
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************
int GetEvenOrOdd()
{
    char ch = ' ';
    int evenOrOdd = 0;
    bool isValid = false;
    
    do
    {
    cout << "Choose whether you would like to search the 'E'ven or 'O'dd numbered cells:" << endl;
    cin >> ch;
    ch = toupper(ch);
    
    switch(ch)
    {
        case 'E':
             evenOrOdd = 0;
             isValid = true;
             break;
        case 'O':
             evenOrOdd = 1;
             isValid = true;
             break;
        default:
             cout << "That was not a valid option" << endl;
             break;
    }//end switch
    }while(!isValid);
 
    return evenOrOdd; 
    
}
    
// *************************************************************************************
// FUNCTION:	SearchLinearHash
// DESCRIPTION:	Searches the linearHashArray for integers stored previously from 
//              the randomArray.
// INPUT:		Parameters:	linearHashArray - array of integers, stored by a 
//                                            hashed address
//                          randomArray - array of random integers
//                          size - the size of the hash table
//                          evenOrOdd - an integer representing even or odd to
//                                      provide a starting place to search
// OUTPUT:		Parameters: N/A
//              Return val: averageCount - average number of searches required
// CALLS TO:	UseModuloDiv - performs the initial hash
// IMPLMENTED BY: Michael Coppock
// ************************************************************************************* 
void SearchLinearHash(int linearHashArray[], int randomArray[], int size, int evenOrOdd, int& searchCount, float& avg)
{
     int i = 0,
         address = 0;
     bool found = false;
     float foundCount = 0;
     
     avg = 0;
     
     i = evenOrOdd;
     
     //loop while there are still random numbers to search for
	 while(i < MAX)
     {
         found = false;
         address = UseModuloDiv(randomArray[i], size);
         
         //inner loop to search for the random number in the hash array
		 while((address < size) && (!found))
         {
             if(randomArray[i] == linearHashArray[address])
             {
                 found = true;
                 searchCount++;
                 foundCount++;
             }
             else
             {
                 searchCount++;
                 address++;
             }
         }
         if(!found && (address < size))
             cout << randomArray[i] << " was not found in the Linear Array" << endl;
             
         i = i + 2;
     }
     
     avg = searchCount / foundCount;
}

// *************************************************************************************
// FUNCTION:	SearchChainedHash
// DESCRIPTION:	Searches the chainedHashArray for integers stored previously from 
//              the randomArray.
// INPUT:		Parameters:	chainedHashArray - array of pointers to linked lists
//                                             of integers
//                          randomArray - array of random integers
//                          size - the size of the hash table
//                          evenOrOdd - an integer representing even or odd to
//                                      provide a starting place to search
// OUTPUT:		Parameters: avg - average number of looks per number
//                          searchCount - the number of looks required
//              Return val: N/A
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// ************************************************************************************* 
void SearchChainedHash(node* chainedHashArray[], int randomArray[], int size, int evenOrOdd, int& searchCount, float& avg)
{
     int i = 0,
         address = 0;
     bool found = false;
     float foundCount = 0;
     
     node* tempNode = new (nothrow) node;
     
     avg = 0;
     
     i = evenOrOdd;
     
     //loop while there are still random numbers to search for
     while(i < MAX)
     {
         found = false;
         address = UseModuloDiv(randomArray[i], size);
         
         tempNode = chainedHashArray[address];
         
         //inner loop to search for the random number in the chained hash array
         while(!found)
         {
             if(tempNode == NULL)
                 cout << randomArray[i] << " was not found at address " << address << endl << endl;
         
             else if(tempNode->num == randomArray[i])
             {
                 found = true;
                 searchCount++;
                 foundCount++;
             }
             else
             {
                 searchCount++;
                 tempNode = tempNode->next;
             }
         
         }//end while
         
         i += 2;
     }//end while

     avg = searchCount / foundCount;
}

// *************************************************************************************
// FUNCTION:	DestroyChainedArray
// DESCRIPTION:	Searches the chainedHashArray for existing linked lists and then
//				calls the DestroyList function to destroy the existing list
// INPUT:		Parameters:	chainedHashArray - array of pointers to linked lists
//                                             of integers
//                          size - the size of the hash table
// OUTPUT:		Parameters: chainedHashArray - array of pointers to linked lists
//                                             of integers
//              Return val: N/A
// CALLS TO:	DestroyList - function to destroy a simple linked list
// IMPLMENTED BY: Michael Coppock
// ************************************************************************************* 
void DestroyChainedArray(node* chainedHashArray[], int size)
{
    int i;
    
    for(i = 0; i < size; i++)
    {
        if(chainedHashArray[i] != NULL)
            DestroyList(chainedHashArray[i]);
    }
}

// *************************************************************************************
// FUNCTION:	DestroyList
// DESCRIPTION:	Destroys a simple linked list
// INPUT:		Parameters:	listTop - pointer to the top of the list
// OUTPUT:		Parameters: N/A
//              Return val: N/A
// CALLS TO:	N/A
// IMPLMENTED BY: Michael Coppock
// *************************************************************************************     
void DestroyList(node* listTop)
{
     node* tempNode = new node;
     
     while(listTop != NULL)
     {
         tempNode = listTop;
         listTop = tempNode->next;
         delete tempNode;
     }
}
