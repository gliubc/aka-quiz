#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	struct stat s;

	chmod("test", 0000);

	/* comment */
	stat("test", &s);
	s.st_mode |= S_IXUSR | S_IXGRP | S_IXOTH;

	chmod("test", s.st_mode);
	
	s.st_mode &= ~S_IRUSR;

	return 0;
}
