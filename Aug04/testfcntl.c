#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd, flags;

	/* open */
	fd = open("flag.c", O_RDONLY);
	
	/* get */
	flags = fcntl(fd, F_GETFL);
	printf("%o\n", flags);

	/* set */
//# define O_APPEND	  02000
	flags |= O_APPEND;	  
//# define O_NONBLOCK	  04000
	flags |= O_NONBLOCK;	  
	fcntl(fd, F_SETFL, flags);

	/* get */
	flags = fcntl(fd, F_GETFL);
	printf("%o\n", flags);

	return 0;
}
