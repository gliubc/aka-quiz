#include <stdlib.h>

void test(void)
{
	malloc(1000);
}

int main(int argc, const char *argv[])
{
	int i;

	for (i = 0; i < atoi(argv[1]); ++i)
		test();
	return 0;
}
