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
	char * args[MAX_ITEMS];
	while(1)
	{
		printf(">"); fgets(cmdln, MAX_LEN, stdin);
	
		nr_items = parseitems(cmdln, items);
	
		if( strcmp(items[0], "exit")==0 )
		{
			printf("Goodbye!\n");
			return 0;
		}
		
		if(nr_items==0)
			continue;
		
		for(i=0; i<MAX_ITEMS; i++)
			args[i]=NULL;
		for(i=0 ; i<nr_items; i++)
			args[i]=items[i];

		if((pid=fork())==0)
		{
			if(execvpe(items[0], args, environ) <0)
			{
				printf("%s: Command not found.\n", items[0]);
				exit(0);
			}
		}
		else
		{
			if(waitpid(pid,&status, 0)<0)
			{
				printf("waitpid error\n");
			}
		}
	}
	return 0;
}
