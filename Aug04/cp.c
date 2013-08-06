/* cp.c */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, const char *argv[])
{
	const char *src, *dest;
	char *p_src, *p_dest;
	int fd_src, fd_dest, len, i;

	/* check input */
	if (argc < 3) {
		puts("Please input ./a.out <src file> <dest file>");
		exit(1);
	}
	src = argv[1];
	dest = argv[2];

	/* open file */
	fd_src = open(src, O_RDONLY);
	if (fd_src < 0) {
		printf("Open %s failed!\n", src);
		exit(1);	
	}
	
	fd_dest = open(dest, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_dest < 0) {
		printf("Open %s failed!\n", dest);
		close(fd_src);
		exit(1);	
	}

	/* get src file length */
	len = lseek(fd_src, 0, SEEK_END);
	printf("len:%d\n", len);

	/* expand dest file */
	lseek(fd_dest, len-1, SEEK_SET);
	write(fd_dest, " ", 1);

	/* mmap */
	p_src = mmap(NULL, len, PROT_READ, MAP_SHARED, fd_src, 0);
	p_dest = mmap(NULL, len, PROT_READ | PROT_WRITE, 
			MAP_SHARED, fd_dest, 0);
	if (p_src == MAP_FAILED) {
		perror("mmap src");
		exit(1);
	}
	if (p_dest == MAP_FAILED) {
		perror("mmap dest");
		exit(1);
	}

	/* copy */
	for (i = 0; i < len; ++i) {
		p_dest[i] = p_src[i];
	}

	/* close file */
	close(fd_src);
	close(fd_dest);

	/* munmap */
	munmap(p_src, len);
	munmap(p_dest, len);
	
	return 0;
}
