#include <stdio.h>

int main(void)
{
	char buf[20] = {0};
	int i;

	//sprintf(buf, "%d", 123);
	//sprintf(buf, "%f", 123.58);
	//sprintf(buf, "%d", 'a');
	//sprintf(buf, "%c", 'a');
	sprintf(buf, "%c", '\0');

	puts(buf);
	for (i = 0; i < 20; ++i) {
		printf("%c:%d ", buf[i], buf[i]);
	}
	putchar('\n');
	return 0;
}
