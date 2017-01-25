#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main()
{
	void* p1, *p2;
	p1 = malloc(10);
	p2 = malloc(100);
	free(p2);
	check_mleak();
	exit(0);
}
