#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>

/* create sub file */
int main(void)
{
	int fd, i, j;
	char name[10], content[10];

	for (i = 0; i < 10; ++i) {
		/* create file name */
		sprintf(name, "%d.txt%c", i+1, '\0');
		/* open sub file */
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644); 

		/* write contents to sub file */
		for (j = 0; j < 10; ++j) {
			sprintf(content, "%d %c", i*10+j+1, '\0');
			write(fd, content, strlen(content));
		}
		write(fd, "\n", 1);

		/* close sub file */
		close(fd);
	}	
	return 0;
}
