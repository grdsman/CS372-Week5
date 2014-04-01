//checks whether a value is a duplicate in an array of integers
bool IsDup(int, int[], int);

//generates random numbers and inserts them into an array
void CreateRandomList(int[]);

//requests input from the user for the hash table size
int GetInput();

//requests input from the user as to whether they would like
//to search for even or odd members of the random array
int GetEvenOrOdd();

//validates the input hash table size
bool IsValidInput(int);

//initializes an array of integers
void InitializeArray(int[], int);

//loads integers into a hash table array
void LoadLinearHashArray(int[], int[], int);

//calculates the initial hash using modulo division
int UseModuloDiv(int, int);

//searches the array for an available location when a
//collision occurs
int LinearProbe(int[], int, int);

//initializes an array of pointers
void InitializeChainedArray(node*[], int);

//gets the hashed address for the random integer and
//calls the AddNode function to load it
void LoadChainedArray(node*[], int[], int);

//loads the chained array with new nodes
void AddNode(node*[], int, int);

//searches the linear hash table for numbers in the
//random integer array
void SearchLinearHash(int[], int[], int, int, int&, float&);

//searches the chained hash table for number from
//the random integer array
void SearchChainedHash(node*[], int[], int, int, int&, float&);

//destroys a list given a list top pointer
void DestroyList(node* listTop);

//finds array locations that have a valid pointer
//and calls the DestroyList function to destroy it
void DestroyChainedArray(node*[], int);
