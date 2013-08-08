#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, const char *argv[])
{
	int val, fd;

	/* check input */
	if (argc < 2) {
		puts("Please input ./a.out <select>");
		exit(1);
	}

	/* redirect */
	switch (atoi(argv[1])) {
		case 1:
			/* < /dev/tty */
			fd = open("/dev/tty", O_RDONLY);
			dup2(fd, STDIN_FILENO);
			//close(fd);
			break;
		case 2:
			/* > temp.foo */
			fd = open("temp.foo", O_WRONLY | O_TRUNC | O_CREAT, 
					S_IRUSR | S_IWUSR);
			dup2(fd, STDOUT_FILENO);
			//close(fd);
			break;
		case 3:
			/* 2>>temp.foo */
			fd = open("temp.foo", O_APPEND | O_CREAT, 
					S_IRUSR | S_IWUSR);
			dup2(fd, STDERR_FILENO);
			//close(fd);
			break;
		case 4:
			/* 5<>temp.foo */
			fd = open("temp.foo", O_RDWR | O_CREAT, 
					S_IRUSR | S_IWUSR);
			if (fd != 5) {
				dup2(fd, 5);
				//close(fd);
			}
			//close(5);
			break;
		case 5:
			/* command > /dev/null 2>&1 */
			fd = open("/dev/null", O_WRONLY);
			dup2(fd, STDOUT_FILENO);
			dup2(STDOUT_FILENO, STDERR_FILENO);
			//close(fd);
			break;
	}
	/* get access mode and file status */
	val = fcntl(fd, F_GETFL);
	printf("%d\n", val);
	
	/* get access mode */
	switch (val & O_ACCMODE) {
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
	}
	/* get status */
	if (val & O_APPEND) {
		printf(", append");
	}
	/* get status */
	if (val & O_NONBLOCK) {
		printf(", nonblocking");
	}
	putchar('\n');
	return 0;
}
