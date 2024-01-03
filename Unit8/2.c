#include <fcntl.h>
#include <stdlib.h>
#include <sys/syscall.h>

//Modify fopen and _fillbuf with fields instead of bit operations

//Read and write permissions for owner, group and others
#define PERMS 0666
#define BUFFSIZE 1024
#define EOF -1


//Max files a program can open simultaneously
#define OPEN_MAX 20  
#define stdin (&_iob [0])
#define stdout (&_iob [1])
#define stderr (&_iob [2])

#define feof(p) ((p) -> flag.isEOF)
#define ferror(p) ((p) -> flag.isErr)
#define fileno(p) ((p) -> file_dtr)

#define getc(p) (--(p) -> cnt >= 0 ? (unsigned char) *(p) -> ptr++ : _fillbuf(p))
#define putc(x,p) (--(p) -> cnt >= 0 ? *(p) -> ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

typedef struct _iobuf 
{
	int cnt;
	char *ptr;
	char *base;
	
	struct flag_field
	{
		unsigned isRead :1;
		unsigned isWrite :1;
		unsigned isUnbuf :1;
		unsigned isBuf :1;
		unsigned isEOF :1;
		unsigned isErr :1;
	} flag;
	int file_dtr;
} FILE;

extern FILE _iob [OPEN_MAX];

//Initialize FILE with stdin, stdout and stderr
FILE _iob [OPEN_MAX] = {
	{0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0, 0}, 0},
	{0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0, 0}, 1},
	{0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0, 0}, 2}
};

//Open file and return a file pointer
FILE *fopen (char *name, char *mode)
{
	int file_dtr;
	FILE *file_ptr;
	
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
		
	for (file_ptr = _iob; file_ptr < _iob + OPEN_MAX; file_ptr++)
		//Found free slot
		if (!file_ptr -> flag.isRead && !file_ptr -> flag.isWrite)
			break;
	//No free slots
	if (file_ptr >= _iob + OPEN_MAX)
		return NULL;
	
	//Create file
	//Write mode
	if (*mode == 'w')
		file_dtr = creat (name, PERMS);	
	//Append mode
	else if (*mode == 'a')
	{
		if ((file_dtr = open (name, O_WRONLY, 0)) == -1)	
			file_dtr = creat (name, PERMS);
		lseek (file_dtr, 0L, 2);
	}
	else
		file_dtr = open (name, O_RDONLY, 0);
		
	if (file_dtr == -1)
		return NULL;
		
	//Initialize members and flags
	file_ptr -> file_dtr = file_dtr;
	file_ptr -> cnt = 0;
	file_ptr -> base = NULL;
	file_ptr -> flag.isUnbuf = 0;
	file_ptr -> flag.isBuf = 1;
	file_ptr -> flag.isEOF = 0;
	file_ptr -> flag.isErr = 0;
	
	if (*mode == 'r')
	{
		file_ptr -> flag.isRead = 1;
		file_ptr -> flag.isWrite = 0;
	}
	else
	{
		file_ptr -> flag.isRead = 0;
		file_ptr -> flag.isWrite = 1;
	}
	
	return file_ptr;
}

//Allocate and read input to buffer
int _fillbuf (FILE *file_ptr)
{
	int buffer_size;
	
	//File can't be read
	if (!file_ptr -> flag.isRead || file_ptr -> flag.isEOF || file_ptr -> flag.isErr)
		return EOF;
		
	buffer_size = (file_ptr -> flag.isUnbuf) ? 1 : BUFFSIZE;
	
	//No buffer exists
	if (file_ptr -> base == NULL)
		//Can't allocate buffer
		if ((file_ptr -> base = (char *)malloc (buffer_size)) == NULL)
			return EOF;
	
	file_ptr -> ptr = file_ptr -> base;
	file_ptr -> cnt = read (file_ptr -> file_dtr, file_ptr -> ptr, buffer_size);
	
	if (--file_ptr -> cnt < 0)
	{
		if (file_ptr -> cnt == -1)
			file_ptr -> flag.isEOF = 1;
		else
			file_ptr -> flag.isErr = 1;
			
		file_ptr -> cnt = 0;
		return EOF;
	}
	
	return (unsigned char) *file_ptr -> ptr++;
}

//Allocate and flush output buffer
int _flushbuf (int x, FILE *file_ptr)
{
	unsigned char_cnt;
	int buffer_size;
	
	if (file_ptr < _iob || file_ptr >= _iob + OPEN_MAX)
		return EOF;
		
	if (!file_ptr -> flag.isWrite | file_ptr -> flag.isErr)
		return EOF;
		
	buffer_size = (file_ptr -> flag.isUnbuf) ? 1 : BUFFSIZE;
	if (!file_ptr -> base)
	{
		if ((file_ptr -> base = (char *)malloc (buffer_size)) == NULL)
		{
			file_ptr -> flag.isErr = 1;
			return EOF;
		}
	}
	else
	{
		char_cnt = file_ptr -> ptr - file_ptr -> base;
		if (write (file_ptr -> file_dtr, file_ptr -> base, char_cnt) != char_cnt)
		{
			file_ptr -> flag.isErr = 1;
			return EOF;
		}
	}
	
	file_ptr -> ptr = file_ptr -> base;
	*file_ptr -> ptr++ = (char) x;
	file_ptr -> cnt = buffer_size - 1;
	
	return x;
}

//Flush buffer associated with file pointer
int fflush (FILE *file_ptr)
{
	int return_code;
	
	if (file_ptr < _iob || file_ptr >= _iob + OPEN_MAX)
		return EOF;
		
	if (file_ptr -> flag.isWrite)
		return_code = _flushbuf (0, file_ptr);
	file_ptr -> ptr = file_ptr -> base;
	file_ptr -> cnt = (file_ptr -> flag.isUnbuf) ? 1 : BUFFSIZE;
	
	return return_code;
}
	
//Close file
int fclose (FILE *file_ptr)
{
	int return_code;
	
	if ((return_code = fflush (file_ptr)) != EOF)
	{
		free (file_ptr -> base);
		file_ptr -> ptr = NULL;
		file_ptr -> cnt = 0;
		file_ptr -> base = NULL;
		file_ptr -> flag.isUnbuf = 0;
		file_ptr -> flag.isBuf = 0;
		file_ptr -> flag.isEOF = 0;
		file_ptr -> flag.isErr = 0;
	}	
	
	return return_code;
}

int main (int argc, char *argv [])
{
	char c;
	
	while ((c = getchar ()) != EOF)
		putchar (c);

	fclose (&_iob [1]);
	return 0;
}


