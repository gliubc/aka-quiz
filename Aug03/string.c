#include <stdio.h>

char *msg = "hello";

int main(void)
{
	char *str = "hello";

	printf("%p\n", msg);
	printf("%p\n", str);
	printf("%p\n", "hello");
	return 0;
}
