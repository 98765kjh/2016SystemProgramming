#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encode(FILE *r, FILE *w, char key)
{
	int i;
	char read[128];
	int fsize=0;
	
	printf("input key (one byte): 0x%X\n",key);
	
	while(1){
		fread(read, 1, 1, r);
		if(feof(r))
			break;
		fsize++;
		//for(i=0; i<strlen(read); i++)
		read[0]^=key;
		fwrite(read, 1, 1, w);
		//fsize+=strlen(read);
	}

	return fsize;
}
void myopen(FILE **r, char* a, FILE **w, char* b)
{
	if( (*r=fopen(a, "rb")) < 0){
		printf("src error\n");
		exit(1);
	}

	if( (*w=fopen(b, "awb+")) < 0){
		printf("dst error\n");
		exit(1);
	}

}
int main (int argc, char** argv)
{
	char* buf = NULL;
	int fsize, ret;
	char key;
	FILE *r, *w;

	/* check arguments */
	if (argc != 4) {
		printf ("usage: myencode src dst key\n");
		exit (-1);
	}

	myopen(&r,argv[1],&w,argv[2]);

	key = (char)atoi(argv[3]);
	
	fsize=encode(r, w, key);
	
	printf("%s is encodded to %s (%d bytes)\n",argv[1],argv[2],fsize);
	
	if((ret=fclose(r))<0)
		printf("close error\n");
	if((ret=fclose(w))<0)
		printf("close error\n");
	return 0;
}

