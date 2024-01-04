#include <stdio.h>
#include <unistd.h>
//Add error checking on malloc and free for size

#define MAX_BYTES (unsigned)10240
#define NALLOC 1024

typedef long Align;
union header 
{
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

static unsigned max_alloc_units;
//Initial empty list
static Header base;
//Start of free list
static Header *free_ptr = NULL;					

//Add block to free list
void free (void *allocated_block)
{
	Header *block_ptr, *ptr;
	
	//Pointer to bloack header
	block_ptr = (Header *)allocated_block - 1;
	
	if (block_ptr -> s.size == 0 || block_ptr -> s.size > max_alloc_units)
	{
		fprintf (stderr, "Cant't free %u units \n", block_ptr -> s.size);
		return;
	}
	
	for (ptr = free_ptr; !(block_ptr > ptr && block_ptr < ptr -> s.ptr); ptr = ptr -> s.ptr)
		if (ptr >= ptr -> s.ptr && (block_ptr > ptr || block_ptr < ptr -> s.ptr))
			break;
			
	//Join to previous neighbour
	if (block_ptr + block_ptr -> s.size == ptr -> s.ptr)
	{
		block_ptr -> s.size += ptr -> s.ptr -> s.size;
		block_ptr -> s.ptr = ptr -> s.ptr -> s.ptr;
	}
	else
		block_ptr -> s.ptr = ptr -> s.ptr;
		
	//Join to next neighbour
	if (ptr + ptr -> s.size == block_ptr)
	{
		ptr -> s.size += block_ptr -> s.size;
		ptr -> s.ptr = block_ptr -> s.ptr;  
	}
	else
		ptr -> s.ptr = block_ptr;
		
	free_ptr = ptr;
}

//Ask system for more memory resources
static Header *morecore (unsigned number_of_units)
{
	char *cp;
	Header *up;
	
	if (number_of_units < NALLOC)
		number_of_units = NALLOC;
		
	cp = sbrk (number_of_units * sizeof (Header));
	if (cp == (char *) - 1)
		return NULL;
		
	up = (Header *) cp;
	up -> s.size = number_of_units;
	max_alloc_units = (up -> s.size > max_alloc_units) ? up -> s.size : max_alloc_units;
	free ((void *) (up + 1));
	
	return free_ptr;
}

//Storage allocator
void *malloc (unsigned number_of_bytes)
{
	Header *ptr, *prev_ptr;
	unsigned number_of_units;
	
	if (number_of_bytes > MAX_BYTES)
	{
		fprintf (stderr, "Can't allocate more than %u bytes\n", MAX_BYTES);
		return NULL;
	}
	
	number_of_units = (number_of_bytes + sizeof (Header) - 1) / sizeof (Header) + 1;
	
	if ((prev_ptr = free_ptr) == NULL)
	{
		base.s.ptr = free_ptr = prev_ptr = &base;
		base.s.size = 0;
	}
	
	for (ptr = prev_ptr -> s.ptr; ; prev_ptr = ptr, ptr = ptr -> s.ptr)
	{
		//Found large enough block
		if (ptr -> s.size >= number_of_units)
		{
			//Block of exact size remove block from freelist
			if (ptr -> s.size == number_of_units)
				prev_ptr -> s.ptr = ptr -> s.ptr;
			//Allocate tail end of block
			else
			{
				ptr -> s.size -= number_of_units;
				ptr += ptr -> s.size;
				ptr -> s.size = number_of_units;
			}
			free_ptr = prev_ptr;
			return (void *)(ptr + 1);
		}
		
		//Wrapped around free list without finding any sufficiently sized block
		if (ptr == free_ptr)
			if ((ptr = morecore (number_of_units)) == NULL)
				return NULL;
	}
}

int main ()
{
	int *ptr = NULL;
	
	ptr = malloc (10);
	
	if (ptr)
	{
		printf ("Allocated space\n");
		free (ptr);
	} 
	else
		printf ("Not enough space\n");
		
	return 0;
}
