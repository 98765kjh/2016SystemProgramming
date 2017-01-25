#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

#include "smalloc1.h"

#define MAX_ITEMS 20


typedef struct {
	int sz;
	int line;
	char file[256];
	void* addr;
} mem_usage;

static int _idx = 0;
static mem_usage _trmem[MAX_ITEMS];


void *smart_malloc_int (size_t size, char *file, int line)
{
	/* TODO: Add your code here */
	void *ptr = malloc(4*size);

	_trmem[_idx].sz = size;
	_trmem[_idx].line = line;
	_trmem[_idx].addr = ptr;
	strcpy(_trmem[_idx].file, file);

	_idx++;

	return ptr;
}

void smart_free_int (void* p, char *file, int line)
{
	/* TODO: Add your code here */
	int i;

	for(i=0; i<MAX_ITEMS; i++){
		if(_trmem[i].addr == p){
			_trmem[i].sz=0;
			_trmem[i].line=0;
			_trmem[i].addr=NULL;
			strcpy(_trmem[i].file, "");
			_idx--;
			free(p);
		}
	}

}

int smart_leakcheck ()
{
	/* TODO: Add your code here */
	int i;
	if(_idx == 0)
		return -1;
	else{
		printf("\n***** MEMORY_BUG DETECTED *****\n");
		for(i=0; i<MAX_ITEMS; i++){
			if(_trmem[i].sz>0){
				printf("[smalloc] leak detected! (file: %s line: %d size: %d addr: %p)\n",_trmem[i].file, _trmem[i].line, _trmem[i].sz, _trmem[i].addr);
			}

		}

	}
	printf("\n");

	return -1;
}

int smart_set_int (void *ptr, int offset, int value, char *file, int line)
{
	/* TODO: Add your code here */
	int i;

	for(i=0; i<MAX_ITEMS; i++){
		if(_trmem[i].addr == ptr){
			if(_trmem[i].sz < offset){
				printf("\n*********************************\n");
				printf("Attemp to access a memory location beyond its size\n");
				printf("Memory Info: addr=%p, size=%d (allocated at %s:%d)\n",_trmem[i].addr, _trmem[i].sz, _trmem[i].file, _trmem[i].line);
				printf("Access Info: offset=%d, size=%d (accessed at %s:%d)\n",offset, _trmem[i].sz, file, line);
				printf("*********************************\n\n");
				return -1;
			}
			else{
				*((int *)_trmem[i].addr+offset) = value;
				return -1;
			}
		}
	}
	
	printf("\n*********************************\n");
	printf("Attemp to access a not-allocated memory location\n");
	printf("Access Info: offset=%d (accessed at %s:%d)\n",offset, file, line);
	printf("*********************************\n\n");

	return -1;
}

int smart_get_int (void *ptr, int offset, char *file, int line)
{
	/* TODO: Add your code here */
	int i;

	for(i=0; i<MAX_ITEMS; i++){
		if(_trmem[i].addr == ptr){
			if(_trmem[i].sz < offset){
				printf("\n*********************************\n");
				printf("Attemp to access a memory location beyond its size\n");
				printf("Memory Info: addr=%p, size=%d (allocated at %s:%d)\n",_trmem[i].addr, _trmem[i].sz, _trmem[i].file, _trmem[i].line);
				printf("Access Info: offset=%d, size=%d (accessed at %s:%d)\n",offset, _trmem[i].sz, file, line);
				printf("*********************************\n\n");
				return -1;
			}
			else{
				return *((int *)ptr+offset);
			}
		}
	}

	return -1;
}

