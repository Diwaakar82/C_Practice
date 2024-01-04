#define NAME_MAX 14

typedef struct
{
	long ino;
	char name [NAME_MAX + 1];
} Dirent;

typedef struct 
{
	int file_dtr;
	Dirent dir;
} DIR;

DIR *opendir (char *dirname);
Dirent *readdir (DIR *dfd);
void closedir (DIR *dfd);
