#include <stdio.h>
#include "test.h"

typedef unsigned char *pointer;

int main(int argc, char** argv)
{
	int a = 15032;
	int b = 19273;

	printf("\n---display Decimal---\n");
	printf("int a = %d\n", a);
	printf("int b = %d\n", b);

	printf("\n---1. display Hex---\n");
	displayHex((pointer)&a, sizeof(int));
	displayHex((pointer)&b, sizeof(int));

	printf("\n---2. display Binary---\n");
	displayBin((pointer)&a, sizeof(int));
	displayBin((pointer)&b, sizeof(int));

	printf("\n---3. swap ---\n");
	printf("a=%d, b=%d\n",a,b);
	swap(&a,&b);
	printf("a=%d, b=%d\n",a,b);
}
