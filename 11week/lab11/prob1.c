#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "smalloc1.h"

int main()
{
	int* p1;
	int* p2;

	p1 = smalloc_int (15);
	p2 = smalloc_int (100);

	printf ("[SET] p1[14] = 101\n");
	sset_int (p1, 14, 101);
	printf ("[GET] p1[14] = ");
	printf ("%d\n", sget_int (p1, 14));

	printf ("[SET] p1[20] = 201\n");
	sset_int (p1, 20, 201);
	printf ("[GET] p1[20] = ");
	printf ("%d\n", sget_int (p1, 20));

	sfree_int (p1);

	printf ("[SET] p1[5] = 10\n");
	sset_int (p1, 5, 10);

	sleak ();

	return 0;
}
