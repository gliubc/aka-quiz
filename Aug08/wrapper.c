#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int in, out;
	char * const args[] = {"./upper", NULL};
	
	/* check input */
	if (argc != 3) {
		fputs("usage: ./a.out file_in file_out", stderr);
	}
	/* redirect */
	in = open(argv[1], O_RDONLY);
	if (in < 0) {
		perror("read");
		exit(1);
	}
	out = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (out < 0) {
		perror("write");
		exit(1);
	}
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);

	/* execute upper */
	execv(args[0], args);

	perror("exec ./upper");
	return 0;
}
