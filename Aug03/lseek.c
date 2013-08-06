/* lseek.c */
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd, l;

	fd = open("cp.c", O_RDWR);

	l = lseek(fd, 0, SEEK_SET);	
	printf("set 0: %d\n", l);

	l = lseek(fd, -10, SEEK_SET);	
	printf("set -10: %d\n", l);

	l = lseek(fd, 0, SEEK_END);	
	printf("end 0: %d\n", l);

	l = lseek(fd, -10, SEEK_END);	
	printf("end -10: %d\n", l);

	l = lseek(fd, 10, SEEK_END);	
	printf("end 10: %d\n", l);
	write(fd, &l, 1);

	close(fd);
	
	fd = open("cp.c", O_RDWR);
	l = lseek(fd, 0, SEEK_END);	
	printf("end 0: %d\n", l);
	close(fd);

	return 0;
}
