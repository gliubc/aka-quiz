#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd, file_size;

	file_size = 1024;
	fd = open("newfile", O_WRONLY | O_CREAT, 0644);
	lseek(fd, file_size-1, SEEK_SET);
	write(fd, " ", 1);
	close(fd);

	return 0;
}
