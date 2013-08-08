#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	struct stat s;

	stat(".", &s);

	//printf("%d\n", s.st_size);
	printf("%o\n", s.st_mode);

	S_ISREG(s.st_mode) ? putchar('-') : putchar('d');
	S_IRUSR & s.st_mode ? putchar('r') : putchar('-');
	S_IWUSR & s.st_mode ? putchar('w') : putchar('-');
	S_IXUSR & s.st_mode ? putchar('x') : putchar('-');
	S_IRGRP & s.st_mode ? putchar('r') : putchar('-');
	S_IWGRP & s.st_mode ? putchar('w') : putchar('-');
	S_IXGRP & s.st_mode ? putchar('x') : putchar('-');
	S_IROTH & s.st_mode ? putchar('r') : putchar('-');
	S_IWOTH & s.st_mode ? putchar('w') : putchar('-');
	S_IXOTH & s.st_mode ? putchar('x') : putchar('-');

	putchar('\n');

	return 0;
}
