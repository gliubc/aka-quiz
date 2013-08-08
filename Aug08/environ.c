#include <stdio.h>

int main(void)
{
	extern char **environ;
	int i;
	
	/* print environment variables */
	for (i = 0; environ[i]; ++i) {
		puts(environ[i]);
	}
	return 0;
}
