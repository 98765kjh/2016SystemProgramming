#include <stdio.h>

int main()
{
	int a=8, b;
	a=a>>2;
	b=a;
	b=b<<2;
	a=a+b;
	printf("%d\n",a);
	return 0;
}
