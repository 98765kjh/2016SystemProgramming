#include <stdio.h>
#include <stdlib.h>

#include "smalloc2.h"

int main()
{
	int* p1;
	int* p2;

	p1 = smalloc_int (15);
	p2 = smalloc_int (100);

	_try {
		printf ("[SET] p1[14] = 101\n");
		sset_int (p1, 14, 101);
		printf ("[GET] p1[14] = ");
		printf ("%d\n", sget_int (p1, 14));

		printf ("[SET] p1[20] = 201\n");
		sset_int (p1, 20, 201);
		printf ("[GET] p1[20] = ");
		printf ("%d\n", sget_int (p1, 20));
	} _catch (illegal_access) {
		printf ("caught an illegal access exception\n");
	} _catch (invalid_pointer) {
		printf ("caught an invalid pointer exception\n");
	} _catch (leak) {
		printf ("caught a memory leak exception\n");
	} _etry


	sfree_int (p1);

	_try {
		printf ("[SET] p1[5] = 10\n");
		sset_int (p1, 5, 10);
	} _catch (illegal_access) {
		printf ("caught an illegal access exception\n");
	} _catch (invalid_pointer) {
		printf ("caught an invalid pointer exception\n");
	} _catch (leak) {
		printf ("caught a memory leak exception\n");
	} _etry


	_try {
		sleak ();
	} _catch (illegal_access) {
		printf ("caught an illegal access exception\n");
	} _catch (invalid_pointer) {
		printf ("caught an invalid pointer exception\n");
	} _catch (leak) {
		printf ("caught a memory leak exception\n");
	} _etry


	return 0;
}

