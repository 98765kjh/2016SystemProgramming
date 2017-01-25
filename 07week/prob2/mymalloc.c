#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>
typedef struct 
{
	void *ptr;
	size_t size;
	char *file;
	int line;
}info;

info data[100];
int num=0;
int check[100]={0};
void *mymalloc(size_t size, char *file, int line)
{
	void *ptr = malloc(size);
	printf("malloc () => addr:%p size:%d file:%s line:%d\n",ptr,(int)size,file,line);
	check[num]=1;

	data[num].ptr=ptr;
	data[num].size=(int)size;
	data[num].file=file;
	data[num].line=line;

	num++;
	
	return ptr;
}

void myfree(void *p, char *file, int line)
{
	int i;
	for(i=0; i<100; i++)
	{
		if(data[i].ptr == p)
		{
			data[i].ptr=NULL;
			data[i].size=-1;
			data[i].file=NULL;
			data[i].line=-1;
			check[i]=0;
			
			break;
		}
	}
	printf("free () => %p\n",p);
	free(p);
}

void check_mleak()
{
	int i;
	printf("[check_mleak]\n");
	for(i=0; i<100; i++)
	{
		if(check[i])
		{
			printf("memory leak detected => file:%s line:%d size:%d addr:%p\n",data[i].file, data[i].line, (int)data[i].size, data[i].ptr);
		}


	}	


}
#endif

