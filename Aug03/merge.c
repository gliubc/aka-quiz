#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int fd, fd_data, i, j, n;
	char name[10], content[10];

	/* open data.txt */
	fd_data = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	for (i = 0; i < 10; ++i) {
		/* create file name */
		sprintf(name, "%d.txt%c", i+1, '\0');
		/* open sub file */
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);

		/* write contents to sub file */
		for (j = 0; j < 10; ++j) {
			sprintf(content, "%d %c", i*10+j+1, '\0');
			write(fd, content, strlen(content));
		}
		write(fd, "\n", 1);

		/* move cursor to the beginning */
		lseek(fd, 0, SEEK_SET);
		/* copy contents of sub file to data.txt */
		while ((n = read(fd, content, sizeof(content))) > 0) {
			//puts(content);
			write(fd_data, content, n);
		}
		
		/* close sub file */
		close(fd);
	}	

	/* close data.txt */
	close(fd_data);
	return 0;
}
