#include <stdio.h>

typedef unsigned char *pointer;
void displayHex(pointer start, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf("%.2x\t", start[i]);
	}
	printf("\n");
}
