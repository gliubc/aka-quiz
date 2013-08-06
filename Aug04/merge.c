#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

/* create sub file */
void create_sub_file(void)
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
}

int main(int argc, const char *argv[])
{
	int i, j, fd_sub, fd_data, len_sub, len_data;
	char name[10], *p_sub, *p_data;
	
	/* create sub file */
	create_sub_file();

	/* merge */

	/* open data.txt */
	fd_data = open("data.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);

	len_data = 0;
	for (i = 0; i < 10; ++i) {
		/* create file name */
		sprintf(name, "%d.txt%c", i+1, '\0');

		/* open sub file */
		fd_sub = open(name, O_RDONLY);
		len_sub = lseek(fd_sub, 0, SEEK_END);

		/* expand data.txt */
		lseek(fd_data, len_sub-1, SEEK_END);
		write(fd_data, " ", 1);	
		len_data = lseek(fd_data, 0, SEEK_END);

		/* mmap sub file */
		p_sub = mmap(NULL, len_sub, PROT_READ, MAP_SHARED, fd_sub, 0);

		/* mmap data.txt */
		p_data = mmap(NULL, len_data, PROT_READ | PROT_WRITE,
				MAP_SHARED, fd_data, 0);

		/* copy */
		for (j = 0; j < len_sub; ++j) {
			p_data[len_data-len_sub+j] = p_sub[j];
		}

		/* munmap sub file */
		munmap(p_sub, len_sub);

		/* munmap data.txt */
		munmap(p_data, len_data);

		/* close sub file */
		close(fd_sub);
	}

	/* close data.txt */
	close(fd_data);

	return 0;
}
