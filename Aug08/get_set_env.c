#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("AAA=%s\n", getenv("AAA"));
	setenv("AAA", "hello", 1);
	unsetenv("AAA");
	printf("AAA=%s\n", getenv("AAA"));

	return 0;
}
