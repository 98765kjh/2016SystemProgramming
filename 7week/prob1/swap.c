int swap(int *x, int *y)
{
	int c=(*x)^(*y);
	*x = c^(*x);
	*y = c^(*y);
}
