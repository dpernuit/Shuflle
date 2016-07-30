#include <iostream>		// for cin/cout
#include <new>          // for std::bad_alloc
#include <ctime>		// for the timer
using namespace std;

//
//	Shuffle
//
//		Input a single integer N.
//		Output the integers 1..N in random order.
//
//		Timers are already included in the program.
//		More than 99% of the duration of the program is due to the output of 
//		all the values to cout.
//		For timing purposes, especially wheb using large values, you can disable
//		the output to cout by setting bOutputAllValues to false.
//
//		The program automatically pauses at the end, using System("PAUSE"),
//		This can be disabled by setting bPauseBeforeEnding to false.
//
//		fastrand is a faster alternative to std::rand()
//		If you wish to use std::rand() instead, set bUseFastRand to false.
//
//		For extremely large values, ie: N = 1 Billion
//		The program should be compiled in x64!
//

static bool bOutputAllValues = false;
static bool bPauseBeforeEnding = false;
static bool bUseFastRand = true;

// bad cast, but will seed the fastrand fine
static int g_nSeed = (int)std::time(NULL);

// fastrand is a faster alternative to std::rand()
inline int fastrand() 
{ 
  g_nSeed = (214013 * g_nSeed + 2531011); 
  return (g_nSeed>>16)&0x7FFF; 
} 

int main() 
{
	// Input N from the user
    int nMAX;
    cin >> nMAX;
	cout << endl;

	// Start the timer
	std::clock_t timerStart = std::clock();
        
    // Error case
    if(nMAX <= 0)
    {
        cout << "Invalid number, please input a number > 0" << endl;
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
			if(bUseFastRand)
				nSwapIndex = fastrand() % (i+1);
			else
				nSwapIndex = std::rand() % (i+1);
			
			
			// It's extremely unlikely it'll happen => waste of time
			// if (nSwapIndex == i)
			//      continue;  
			
			// Swap values at nSwapIndex and i
			nTemp = tValues[nSwapIndex];
			tValues[nSwapIndex] = tValues[i];
			tValues[i] = nTemp;
		}
		
		// Shuffle finished!
		double dShuffleDuration = (std::clock() - timerStart);

		if(bOutputAllValues)
		{
			// Output each value in a row
			for(int n = 0; n < nMAX; n++)
				cout << tValues[n] << endl;  
		}
		
		// Clean the memory
		delete[] tValues;

		// Output the duration times
		double dDuration = (std::clock() - timerStart);
		cout << "Shuffled in " << dShuffleDuration << " ms." << endl;
		cout << "Total time: " << dDuration << " ms." << endl;
	}
	catch (std::bad_alloc& ba)
	{
		// Not enough memory, please compile me in X64 ;)
		cout << ba.what() << " Not enough memory to allocate the array" << endl;   
	}
	catch(...)
	{
		cout << "An exception occurred!" << endl; 
	}

	// Pause the program before returning (Windows only)
	if(bPauseBeforeEnding)
		system("PAUSE");

	return 0;   
}
