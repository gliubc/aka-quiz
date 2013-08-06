#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int fd, n, i;
	char name[] = "?.txt";

	if (argc < 2) {
		puts("Please input ./a.out N");
		exit(1);
	}
	n = atoi(argv[1]);

	for (i = 0; i < 5; ++i) {
		name[0] = i + '1';
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		lseek(fd, n-1, SEEK_SET);
		write(fd, " ", 1);
		close(fd);
	}	

	return 0;
}
