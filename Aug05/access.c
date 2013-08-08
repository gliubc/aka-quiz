#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int ret;

	ret = access("stat.c", F_OK);
	if (ret == 0) {
		puts("file is there");
		ret = access("stat.c", R_OK);
		if (ret == 0) {
			puts("file can be read");
		}
		ret = access("stat.c", W_OK);
		if (ret == 0) {
			puts("file can be written");
		}
		ret = access("stat.c", X_OK);
		if (ret == 0) {
			puts("file is executive");
		}
		ret = access("stat.c", R_OK | W_OK);
		if (ret == 0) {
			puts("read write");
		}
	}
	return 0;
}
