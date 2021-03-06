#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copy(FILE *r, FILE *w)
{
	char read[100000];

	fread(read, 100000, 1, r);
	if(fwrite(read, strlen(read), 1, w)<0){
		return 0;
	} 

	return strlen(read);
}

void myopen(FILE **r, char* a, FILE **w, char* b)
{
	if( (*r=fopen(a, "r")) < 0){
		printf("src error\n");
		exit(1);
	}

	if( (*w=fopen(b, "w+")) < 0){
		printf("dst error\n");
		exit(1);
	}

}
int main (int argc, char** argv)
{
	char* buf = NULL;
	int fsize, ret;
	FILE *r, *w;

	/* check arguments */
	if (argc != 3) {
		printf ("usage: mycp src dst\n");
		exit (-1);
	}

	myopen(&r, argv[1], &w, argv[2]);
	
	if((fsize=copy(r,w))<0){
		printf("copy fail\n");
		exit(1);
	}
	else{
		printf("%s is copied to %s (%d bytes)\n",argv[1],argv[2],fsize);
	}
	
	return 0;
}

