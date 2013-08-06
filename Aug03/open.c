#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void test01(void)
{
	int fd;

	fd = open("a.txt", O_RDONLY);
	if (fd < 0) {
		perror("Open a.txt failed");
		exit(1);
	}
	close(fd);
}

void test02(void)
{
	int fd;

	fd = open(".", O_WRONLY);
	if (fd < 0) {
		perror("Open current directory failed");
		exit(1);
	}
	close(fd);
}

void test03(void)
{
	int fd;

	fd = open("./test", O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("Open dir failed");
		exit(1);
	}
	close(fd);
}

void test04(void)
{
	int fd;

	fd = open("test", O_WRONLY | O_APPEND);
	if (fd < 0) {
		perror("Open test failed");
		exit(1);
	}
	close(fd);
}

void test05(void)
{
	int fd;

	fd = open("test", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0) {
		perror("Open test failed");
		exit(1);
	}
	close(fd);
}

void test06(void)
{
	int fd;

	fd = open("test", O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd < 0) {
		perror("Open test failed");
		exit(1);
	}
	close(fd);
}

void test07(void)
{
	char buf[10];
	int n;

	n = read(STDIN_FILENO, buf, 10);
	if (n < 0) {
		perror("Read STDIN_FILENO");
		exit(1);
	}

	write(STDOUT_FILENO, buf, n);
}

int main(void)
{
	puts("test 7");
	test07();	

	return 0;
}
