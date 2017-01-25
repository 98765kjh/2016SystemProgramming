#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAX_ITEMS	10
#define MAX_LEN		256
#define MAX_BG_ITEMS	3
#define MAX_STACK 	10000
extern char **environ;

typedef struct PPID{
	pid_t pid;
	char cmd[MAX_LEN];
}PPID;

PPID P[MAX_BG_ITEMS];
int num=0;
pid_t stack[MAX_STACK];
int Spos=0;

int parseitems (char* cmdln, char items[][MAX_LEN])
{
	int i = 0;
	char* pch = NULL;

	pch = strtok (cmdln, " \n");
	while (pch != NULL && i < MAX_ITEMS) {
		strcpy (items[i], pch);
		pch = strtok (NULL, " \n");
		i++;
	}

	return i;
}

void child_handler(int sig)
{
	int i, child_status;
	pid_t pid;
	while( (pid=waitpid(-1, &child_status, WNOHANG) ) > 0){
		for(i=0; i<MAX_BG_ITEMS; i++)
			if(P[i].pid == pid){
				P[i].pid=-1;
				printf("\n[%d] finished\n>", pid);
				Spos--;
				num--;
			}
	
	}
}
void killone(int pid)
{
	int i, child_status;
	pid_t wpid;
	int tmp;

	kill(pid, SIGKILL);

	tmp=num;
	//wpid=wait(&child_status);
	waitpid(pid, &child_status, 0);
	if(WIFSIGNALED(child_status)){
		for(i=0; i<MAX_BG_ITEMS; i++)
			if(P[i].pid == pid){
				P[i].pid=-1;
				printf("[%d] killed forcedly by you!\n", pid);
				num--;
				Spos--;
			}
		return;
	}
	if(tmp==num){
		printf("%d: pid not found\n", pid);
	}
	
}
void killemall()
{
	int i, child_status;
	pid_t wpid;
	int tmp;
	
	for(i=0; i<MAX_BG_ITEMS; i++)
		if(P[i].pid != -1)
		{
			killone(P[i].pid);
		}
	/*
	kill(-1, SIGKILL);

	tmp=num;
	for(i=0; i<tmp; i++)
	{
		wpid=wait(&child_status);
		if(WIFSIGNALED(child_status)){
			printf("[%d] killed forcedly by you!\n>", wpid);
		}
		else{

		}


	}
	*/
}

int main (int argc, char* argv[])
{
	char cmdln[MAX_LEN];
	char items[MAX_ITEMS][MAX_LEN];
	int nr_items;
	pid_t pid;
	int status, bg;
	int i;
	
	char* args[MAX_ITEMS];	
	
	signal(SIGCHLD, child_handler);

	// Initialize
	for(i=0; i<MAX_BG_ITEMS; i++)
		P[i].pid = -1;

	while(1)
	{
		usleep(1000 * 10);
		printf(">"); fgets(cmdln, MAX_LEN, stdin);
		bg=0;
		nr_items = parseitems ( cmdln, items );

		// Check EXIT
		if( strcmp(items[0], "exit")==0 )
		{
			printf("Goodbye!\n");
			return 0;
		}
		// Check STATUS
		if( strcmp(items[0], "status")==0 )
		{
			for(i=0; i<MAX_BG_ITEMS; i++)
			{
				if(P[i].pid!=-1)
					printf("[%d] %s\n", P[i].pid, P[i].cmd);
			}
			strcpy(items[0],"");
			continue;
		}
		// Check # of argument
		if(nr_items==0)
			continue;
		
		/*
		// Check Close
		if(strcmp(items[0], "close")==0)
		{
			pid=atoi(items[1]);
			for(i=0; i<MAX_BG_ITEMS; i++)
			{
				if(P[i].pid == pid)
				{
					P[i].pid=-1;
					waitpid(pid, &status, 0);
					printf("[%d] closed\n", pid);
					num--;
				}
			}
			continue;
		}
		*/
		if(strcmp(items[0], "killone")==0)
		{
			pid=atoi(items[1]);
			killone(pid);
			continue;
		}
		if(strcmp(items[0], "killemall")==0)
		{
			killemall();
			continue;
		}
		if(strcmp(items[0], "fg")==0)
		{
			if(num==0)
				printf("no background process\n");
			else
			{
				waitpid(stack[Spos-1], &status, 0);
				for(i=0; i<MAX_BG_ITEMS; i++){
					if(P[i].pid==stack[Spos-1])
						P[i].pid=-1;
				}
				Spos--;
				num--;
				
			}
			continue;
		}
		// Check background
		if(strcmp(items[nr_items-1],"&")==0)
		{
			// Check Maximum
			if(num>=MAX_BG_ITEMS)
			{
				printf("Failed: maximum # of background job is %d\n",MAX_BG_ITEMS);
				continue;
			}
			else bg=1;
		}
		
		if(bg)	nr_items--;
		// Erase buffer	
		for(i=0; i<MAX_ITEMS; i++)
			args[i]=NULL;
		for(i=0; i<nr_items; i++)
			args[i]=items[i];
		
		if((pid=fork())==0)
		{
			if(bg){
				printf("[%d] %s \n", getpid(), items[0]);
				
			}
			if(execvpe(items[0], args, environ) <0)
			{
				printf("%s: Command not found.\n", args[0]);
				exit(0);
			}
		}
		else
		{
			if(!bg)
			{
				if(waitpid(pid, &status, 0) < 0 )
					printf("waitpid error\n");
			}
			else
			{
				for(i=0; i<MAX_BG_ITEMS; i++)
				{
					if(P[i].pid==-1)
					{
						P[i].pid=pid;
						strcpy(P[i].cmd, args[0]);
						stack[Spos]=pid;
						break;
					}
				}
				Spos++;
				num++;
			}
		}
	}
	return 0;
}
