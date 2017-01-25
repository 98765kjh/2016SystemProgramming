#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>

void *mymalloc(size_t size, char *file, int line)
{
	void *ptr = malloc(size);
	printf("%s:%d: malloc(%d)=%p\n", file, line, (int)size, ptr);
	return ptr;
}

void myfree(void *p, char *file, int line)
{
	free(p);
}

#endif

