#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ITEMS	10
#define MAX_LEN		256

extern char **environ;

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

int main (int argc, char* argv[])
{
	char cmdln[MAX_LEN];
	char items[MAX_ITEMS][MAX_LEN];
	int nr_items;
	int i;
	pid_t pid;
	int status;
	execvpe("ps","ps",environ);	
	//strcpy (cmdln, "Test string");
	while(1)
	{	
		printf(">");	gets(cmdln);
		if(strcmp(cmdln,"exit")==0)
		{
			printf("Goodbye!\n");
			break;
		}
			
		nr_items = parseitems (cmdln, items);
		printf("%d\n",nr_items);
		pid=fork();
		if(pid==0)
		{
			if(execvpe(items[0], items, environ) < 0)
	
			{
				printf("%s: Command not found.\n", items[0]);
				exit(0);
			}
		}
		else
		{
			if(waitpid(pid, &status, 0) < 0)
			{
				printf("waitfg: waitpid error\n");

			}
			else
			{
				printf("child process end.\n");
			}
		}
	}
	return 0;
}
