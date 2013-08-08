#include <stdio.h>

int main(void)
{
	int a;
	int *p = &a;
	int *q = p + 1;

	printf("%d\n", q-p);
	printf("%p\n", p);
	printf("%p\n", q);
	return 0;
}
