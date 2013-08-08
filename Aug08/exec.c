#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *const ps_argv[] = {"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL};
	char *const ps_envp[] = {"PATH=/bin:/usr/bin", "TERM=console", NULL};

	//execl("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
	//execlp(ps_argv[0], "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
	//execle("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);
	//execv("/bin/ps", ps_argv);
	//execvp(ps_argv[0], ps_argv);
	execve("/bin/ps", ps_argv, ps_envp);

	perror("exec ps");
	exit(1);
}
