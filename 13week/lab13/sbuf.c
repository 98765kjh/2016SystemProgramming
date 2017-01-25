#include <stdlib.h>
#include <stdio.h>
#include "sbuf.h"

/* create an empty, bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n)
{
	//printf("sbuf_init\n");
	sp->in = sp->out = 0;
	sp->buffer = (double*)malloc(sizeof(double)*n);
	sem_init(&sp->empty, 0, n);
	sem_init(&sp->full, 0, 0);
	sem_init(&sp->mutex, 0, 1);
	sp->num = 0;
}

/* clean up buffer sp */
void sbuf_deinit(sbuf_t *sp)
{
	free(sp->buffer);
}

/* insert item onto the rear of shared buffer sp */
void sbuf_insert(sbuf_t *sp, double item)
{
	sem_wait(&sp->mutex);

	sp->buffer[sp->in] = item;
	sp->in=(sp->in+1)%1000000;
	sp->num++;

	sem_post(&sp->mutex);
}

/* remove and return the first item from buffer sp */
double sbuf_remove(sbuf_t *sp)
{
	double ret;
	sem_wait(&sp->mutex);

	ret = sp->buffer[sp->out];
	sp->out = (sp->out+1)%1000000;
	sp->num--;

	sem_post(&sp->mutex);
	return ret;
}

