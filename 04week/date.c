#include <stdio.h>

unsigned int g_year(unsigned int date)
{
	printf("%d\n",date>>9);
}

unsigned int g_month(unsigned int date)
{
	printf("%d\n",(date>>5)&511);
}


unsigned int g_day(unsigned int date)
{
	printf("%d\n",date&31);
}

int main()
{
	unsigned int date = 1032310;

	g_year(date);
	g_month(date);
	g_day(date);

	return 0;
}
