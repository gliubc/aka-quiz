#include <stdio.h>

int main(void)
{
	/* < /dev/tty */
	fd = open("/dev/tty", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);

	/* > temp.foo */
	fd = open("temp.foo", O_WRONLY | O_TRUNC | O_CREAT, O_IRUSR | O_IWUSR);
	dup2(fd, STDOUT_FILENO);
	close(fd);

	/* 2>>temp.foo */
	fd = open("temp.foo", O_APPEND | O_CREAT, O_IRUSR | O_IWUSR);
	dup2(fd, STDERR_FILENO);
	close(fd);

	/* 5<>temp.foo */
	fd = open("temp.foo", O_RDWR | O_CREAT, O_IRUSR | O_IWUSR);
	if (fd != 5) {
		dup2(fd, 5);
		close(fd);
	}
	close(5);

	/* command > /dev/null 2>&1 */
	fd = open("/dev/null", O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	close(fd);
		
	return 0;
}
