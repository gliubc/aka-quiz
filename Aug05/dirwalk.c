#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH 1024

void copy(const char *src, const char *dest)
{
	char buf[10];
	int fd_src, fd_dest, n;

	/* open file src */
	fd_src = open(src, O_RDONLY);
	if (fd_src < 0) {
		printf("Open %s failed!\n", src);
		exit(1);	
	}
	/* open file dest */
	fd_dest = open(dest, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_dest < 0) {
		printf("Open %s failed!\n", dest);
		close(fd_src);
		exit(2);	
	}
	/* copy */
	while ((n = read(fd_src, buf, 10)) > 0) {
		write(fd_dest, buf, n);
	}
	/* close */
	close(fd_src);
	close(fd_dest);
}

void dirwalk(const char *dir)
{
	char name[MAX_PATH];
	struct stat stbuf;
	DIR *dfd;
	struct dirent *dp;

	if ((dfd = opendir(dir)) == NULL) {
		printf("dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0
				|| strcmp(dp->d_name, "..") == 0) {
			continue;	/* skip self and parent */
		}
		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
			continue;
		}
		sprintf(name, "%s/%s", dir, dp->d_name);
		stat(name, &stbuf);
		if (S_ISREG(stbuf.st_mode)) {
			puts(dp->d_name);
		} else if (S_ISDIR(stbuf.st_mode)) {
			dirwalk(name);
		}
	}
	closedir(dfd);
}

int main(int argc, const char *argv[])
{
	if (argc == 1) {	/* default: current directory */
		dirwalk(".");
	} else {
		dirwalk(argv[1]);
	}
	return 0;
}
