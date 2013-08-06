/* mmap.c */
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd, len, i;
	char *p;

	/* open file */
	fd = open("hello", O_RDONLY);
	if (fd < 0) {
		perror("open hello");
		exit(1);
	}

	/* get file length */
	len = lseek(fd, 0, SEEK_END);
	printf("len:%d\n", len);

	/* mmap */
	p = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	/* close file */
	close(fd);

	/* output file */
	for (i = 0; i < len; ++i) {
		putchar(p[i]);
	}

	/* unmap */
	munmap(p, len);

	return 0;
}
