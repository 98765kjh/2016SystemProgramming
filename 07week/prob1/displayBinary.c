#include <stdio.h>
typedef unsigned char *pointer;
void displayBin(pointer start, int len)
{
	int i,j;
	int b=128;
	for(i=0; i<len; i++)
	{
		for(j=0; j<8; j++)
		{
			if( (start[i]<<j)&b )
				printf("1");
			else
				printf("0");

			if(j==3 || j==7)
				printf(" ");
		}
	}
	printf("\n");
}
