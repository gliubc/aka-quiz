/* fcntl.c */
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	int flags, n;
	char buf[10];

	flags = fcntl(STDIN_FILENO, F_GETFL);
	flags |= O_NONBLOCK;
	if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) {
		perror("fcntl");
		exit(1);
	}

tryagain:
	n = read(STDIN_FILENO, buf, 10);
	if (n <= 0) {
		if (errno != EAGAIN) {
			perror("read");
			exit(1);
		}
		sleep(1);
		write(STDOUT_FILENO, "Try again!\n", strlen("Try again!\n"));
		goto tryagain;
	}

	write(STDOUT_FILENO, buf, n);
	return 0;
}
