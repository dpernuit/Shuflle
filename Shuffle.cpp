#include <iostream>		// for cin/cout
#include <new>          // for std::bad_alloc
using namespace std;

int main() 
{
    int nMAX;
    cin >> nMAX;
    
    // Error case
    if(nMAX <= 0)
    {
        cout << "Invalid number, please input a number > 0" << endl;
        return 0;
    }        
    
    // Simplest case
    if (nMAX == 1)
    {
        cout << "1" << endl;
        return 0;
    }
    
    // Building an array of all the values [1 .. N] 
	try
	{
		// Using new to allocate memory on the heap
		int* tValues = new int[nMAX];
		
		// Intializes the array with values from 1..N
		for(int n = 0; n < nMAX; n++)
		{
			tValues[n] = n+1;
		}
		
		// Starting from the end of the array, we'll swap the current value
		// with a random one. All the values with an index > i are already shuffled
		int nSwapIndex = 0, nTemp = 0;
		for(int i = nMAX-1; i > 0; i--)
		{
			// Returns a random number betwen 0 and i
			nSwapIndex = std::rand() % (i+1);
			
			// Extremely unlikely it happens => waste of time
			// if (nSwapIndex == i)
			//      continue;  
			
			// Swap values at nSwapIndex and i
			nTemp = tValues[nSwapIndex];
			tValues[nSwapIndex] = tValues[i];
			tValues[i] = nTemp;
		}
		
		// Output each value in a row
		for(int n = 0; n < nMAX; n++)
			cout << tValues[n] << endl;  
		
		// Clean the memory
		delete[] tValues;
	}
	catch (std::bad_alloc& ba)
	{
		// Not enough memory, please compile me in X64 ;)
		cout << "Failed to allocate the array";   
	}
	catch(...)
	{
		cout << "Exception occurred";
	}

	return 0;   
}
