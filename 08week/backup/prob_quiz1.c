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

	while(1)
	{
		printf(">"); fgets(cmdln,MAX_LEN,stdin);

		nr_items = parseitems(cmdln, items);

		if( strcmp(items[0], "exit")==0 )
		{
			printf("Goodbye!\n");
			return 0;
		}

		if(nr_items==0)
			continue;

		printf("# of arguments: %d\n", nr_items);

		for(i=0; i<nr_items; i++)
		{
			printf("-argv[%d]: %s\n",i, items[i]);
			
		}
	}
	return 0;
}
