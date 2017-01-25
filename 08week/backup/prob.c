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

	strcpy (cmdln, "Test string");
	nr_items = parseitems (cmdln, items);
	printf ("%d\n%s\n%s\n", nr_items, items[0], items[1]);

	return 0;
}
