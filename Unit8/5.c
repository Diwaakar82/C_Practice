#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include "dirent.h"
//Modify fsize to print inode details

#define MAX_PATH 1024
#ifndef DIRSIZ
#define DIRSIZ 14
#endif

struct direct
{
	ino_t d_ino;
	char d_name [DIRSIZ];
};

//Open a directory
DIR *opendir (char *dir_name)
{
	int file_dtr;
	struct stat status_buffer;
	DIR *dir_ptr;
		
	if ((file_dtr = open (dir_name, O_RDONLY, 0)) == -1 || fstat (file_dtr, &status_buffer) == -1 || (status_buffer.st_mode & S_IFMT) != S_IFDIR || (dir_ptr = (DIR *) malloc (sizeof (DIR))) == NULL)
		return NULL;
	dir_ptr -> file_dtr = file_dtr;
	
	return dir_ptr;
}

//Close opened directory
void closedir (DIR *dir_ptr)
{
	if (dir_ptr)
	{
		close (dir_ptr -> file_dtr);
		free (dir_ptr);
	}
}

//Read directory contents
Dirent *readdir (DIR *dir_ptr)
{
	struct direct dir_buffer;
	static Dirent d;
	
	while (read (dir_ptr -> file_dtr, (char *) &dir_buffer, sizeof (dir_buffer)) == sizeof (dir_buffer))
	{
		if (dir_buffer.d_ino == 0)
			continue;
			
		d.ino = dir_buffer.d_ino;
		strncpy (d.name, dir_buffer.d_name, DIRSIZ);
		d.name [DIRSIZ] = '\0';
		
		return &d;
	}
	
	return NULL;
}

//Apply function to all the files in the directory dir
void dirwalk (char *dir, void (*function)(char *))
{
	char name [MAX_PATH];
	Dirent *dir_ptr;
	DIR *dir_file_dtr;
	
	if ((dir_file_dtr = opendir (dir)) == NULL)
	{
		fprintf (stderr, "Can't open %s\n", dir);
		return;
	}
	
	while ((dir_ptr = readdir (dir_file_dtr)) != NULL)
	{
		//Skip self and parent directories
		if (!(strcmp (dir_ptr -> name, ".")) || !(strcmp (dir_ptr -> name, "..")))
			continue;
		if (strlen (dir) + strlen (dir_ptr -> name) + 2 > sizeof (name))
			fprintf (stderr, "name %s/%s too long\n", dir, dir_ptr -> name);
		else
		{
			sprintf (name, "%s/%s", dir, dir_ptr -> name);
			(*function)(name);
		}
	}
	
	closedir (dir_file_dtr);
}

void fsize (char *name)
{
	struct stat status_buffer;
	
	if (stat (name, &status_buffer) == -1)
	{
		fprintf (stderr, "Can't access %s\n", name);
		return;
	}
	if ((status_buffer.st_mode & S_IFMT) == S_IFDIR)
		dirwalk (name, fsize);
	printf ("Name: %s\nInode number: %u\nStatus mode: %o\nNumber of links: %u\nSize: %ld\n", name, status_buffer.st_ino, status_buffer.st_mode, status_buffer.st_nlink, status_buffer.st_size);
}

int main (int argc, char **argv)
{
	if (argc == 1)
		fsize (".");
		
	else
		while (--argc)
			fsize (*++argv);
			
	return 0;
}
