#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void segf(int sig)
{
	printf("segmentation fault occurs!\n");
	exit(0);
}

int main (int argc, char** argv)
{
	/* TODO: Impelement your code here */
	int a[3],i;
	signal(SIGSEGV, segf);

	for(i=0; i<1000; i++)
		a[i]=0;

	return 0;
}

