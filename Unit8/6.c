#include <sys/syscall.h>
#include <stdlib.h>
#include <stdio.h>

//Simulate calloc by calling malloc

//Allocate objects of size size
void *mycalloc (unsigned number_of_objects, unsigned size)
{
	unsigned i, number_of_bytes;
	char *head, *ptr;
	
	//Allocate space using malloc	
	if ((ptr = head = malloc (number_of_bytes)) != NULL)
		//Iterate through the allocated objects and initialize to 0
		for (i = 0; i < number_of_bytes; i++)
			*ptr++ = 0;
			
	return head;
}

int main ()
{
	int *ptr = NULL;
	
	ptr = mycalloc (10, sizeof (*ptr));
	
	if (ptr)
	{
		for (int i = 0; i < 10; i++)
			printf ("%d ", ptr [i]);
		printf ("\n");
		
		free (ptr);
	} 
	else
		printf ("Not enough space\n");
		
	return 0;
}
