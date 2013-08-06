#include <stdio.h>

int main(void)
{
	char str[] = "秃鹰之一种a";
	int i;
	
	str[6] = '\0';
	puts(str);
	for (i = 0; i < sizeof(str); ++i) {
		//printf("%x ", str[i]);
	}
#if 0
	putchar(0xffffffe7);
	putchar(0xffffffa7);
	putchar(0xffffff83);
#endif
	return 0;
}
