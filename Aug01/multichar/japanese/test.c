#include <stdio.h>
#include <string.h>

int main(void)
{
#if 0
	char str[] = "わりかん", *p;

	p = str+6;
	puts(str);
	puts(p);
	memmove(str, p, 7);
	puts(str);
#endif 
	/* 1womendoushihaohaizi1 */
	char *str1 = "abhelloworldcdhell1womendoushihaohaizi1owoahelloworld23";
	char *str2 = "afafafhello1womendoushihaohaizi1world22";
	int len1, len2, i, begin1, begin2, sum, max;

	len1 = strlen(str1);
	len2 = strlen(str2);
	sum = max = 0;

	/* total area */
	for (i = 0; i <= len1+len2-3; ++i) {
		if (i <= len2) {
			begin1 = 0;
			begin2 = len2 - i;
		} else {
			begin1 = i - len2;
			begin2 = 0;
		}

		/* compare area */
		for ( ; begin1 < len1 && begin2 < len2; ++begin1, ++begin2) {
			if (str1[begin1] == str2[begin2]) {
				++sum;
			} else {
				max = max > sum ? max : sum;
				sum = 0;
			}
		}	
	}
	printf("%d\n", max);

	return 0;
}
