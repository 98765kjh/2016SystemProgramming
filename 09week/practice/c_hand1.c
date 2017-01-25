#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int ccount=0;
void child_handler(int sig)
{
	int child_status;
	pid_t pid = wait(&child_status);
	ccount--;
	printf("Received signal %d from process %d\n", sig, pid);
	printf("ccount: %d\n",ccount);
}

void child_handler2(int sig)
{
	int child_status;
	pid_t pid;
	while( (pid=waitpid(-1, &child_status, WNOHANG) ) > 0){
		ccount--;
		printf("Received signal %d from process %d\n", sig, pid);
	}
}
main()
{
	pid_t pid[5];
	int i, child_status;
	ccount=5;
	signal(SIGCHLD, child_handler2);
	for(i=0; i<5; i++)
		if( (pid[i]=fork()) == 0){
			sleep(1);
			exit(0);
		}
	while(ccount>0)
		pause();
}
