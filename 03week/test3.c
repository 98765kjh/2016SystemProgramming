#include <stdio.h>

int main(void)
{
	int i=0, j=0;
	int k=0;
	while(i<5)
	{
	k=0;
	while(k<5-i)
	{
		printf(" ");
		k++;
	}
	printf("*");
		while(j<i){
			printf("oo");
			j++;
		}
	j=0;
	printf("*\n");
	i++;
	}
	return 0;
}
