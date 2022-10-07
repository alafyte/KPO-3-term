#include <iostream>


extern "C"
{
	int getmax(int* mas, int size)
	{
		int max = 0;
		for (int i = 0; i < size; i++)
		{
			if (mas[i] > max) 
				max = mas[i];
		}
		return max;
	}

	int getmin(int* mas, int size)
	{
		int min = INT_MAX;
		for (int i = 0; i < size; i++)
		{
			if (mas[i] < min) 
				min = mas[i];
		}
		return min;
	}
}