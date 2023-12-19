#include <stdio.h>

//Improve the given binary search which does 2 conditional checks into just one check.

//Function to perform binary search on an array.
int binary_search (int arr [], int length, int element)
{
	int low = 0, high = length - 1;

	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (arr [mid] < element)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (arr [low] == element) ? low : -1;
}

int main ()
{
	int arr [10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int element;
	scanf ("%d", &element);

	int result = binary_search (arr, 10, element);
	
	if (result == -1)
		printf ("Element not found.\n");
	else
		printf ("Element found at: %d\n", result);	
	return 0;
}
