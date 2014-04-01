//loads the double hash array table with integers
//in hashed address locations
bool LoadDoubleHashArray(int[], int[], int);

//calculates the double hash address
bool DoubleHash(int[], int, int&, int);

//Calculates the load factor
float GetLoadFactor(int);

//calls other search functions and gathers data about the
//search results
void HashAnalysis(bool, int[], int[], node*[], int[], int, int, float);

//searches the double hash table for integers from
//the random integer array
void SearchDoubleHash(int[], int[], int, int, int&, float&);

//calculates the Knuth average for a given load factor
//and type of hash being used
void GetKnuthAverage(float, float&, float&, float&);

//displays the results of the searches to the screen
void PrintResults(bool, int, int, int, int, float, float, float, float, float, float, float);
