#include <stdio.h>
#include <unistd.h>

//int i = 0;

int main(void)
{
	static int i = 0;

	while (1) {
		sleep(1);
		printf("&i=%p i=%d\n", &i, i);
		++i;
	}
	return 0;
}
