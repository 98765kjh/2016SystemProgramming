#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define NAME_LEN 256

typedef struct{
	int len;
	int nr_srcfiles;
	char name[10][256];
	int file_len[10];
}Header;

void merge(FILE *dst, char (*buf)[256], int nr_srcfiles, char key)
{
	struct stat st;
	int i;
	FILE *r;
	char read[100];
	Header Hd;

	Hd.len = 0;
	Hd.nr_srcfiles = nr_srcfiles;
	/*Hd.name = (char**)malloc(sizeof(char*) * nr_srcfiles);
	for(i=0; i<nr_srcfiles; i++){
		Hd.name[i] = (char*)malloc(sizeof(char)*NAME_LEN);
	}
	Hd.file_len = (int*)malloc(sizeof(int) * nr_srcfiles);
	*/

	for(i=0; i<nr_srcfiles; i++){
		
		r = fopen(buf[i], "r");
		
		fseek(r, 0, SEEK_END);
		Hd.file_len[i] = ftell(r);
		fseek(r, 0, SEEK_SET);
		
		printf("Hd.file_len[%d]: %d\n", i, Hd.file_len[i]);

		strcpy(Hd.name[i], buf[i]);
		
		printf("Hd.name[%d]: %s\n", i, Hd.name[i]);		

		fclose(r);
	}

	Hd.len = sizeof(Hd);
	printf("Hd.len : %d\n", Hd.len);	//Debug
	fwrite(&Hd, sizeof(Hd), 1, dst);
	
	for(i=0; i<nr_srcfiles; i++){
		r=fopen(buf[i], "r");
		
		while(1){
			fread(read, 1, 1, r);
			if(feof(r))
				break;
			
			read[0]^=key;
			fwrite(read, 1, 1, dst);
			//fsize+=strlen(read);
		}
	}

}

void myopen(FILE **w, char *a)
{
	*w=fopen(a,"wa");
}
int main (int argc, char** argv)
{
	unsigned char** buf = NULL;
	int* fsize;
	int ret, nr_srcfiles, i;
	char mybuf[10][256];
	char key;
	FILE *dst;

	/* check arguments */
	if (argc < 4) {
		printf ("usage: mymerge mergedfile key srcfile1 srcfile2 ...\n");
		exit (-1);
	}

	myopen(&dst, argv[1]);

	nr_srcfiles = argc-3;
	//mybuf = (char**)malloc(sizeof(char*)*nr_srcfiles);
	for(i=0; i<nr_srcfiles; i++){
		//mybuf[i] = (char*)malloc(sizeof(char)*NAME_LEN);
		strcpy(mybuf[i], argv[3+i]);
		
	}
	key = (char)atoi(argv[2]);

	merge(dst, mybuf, nr_srcfiles, key);
	printf("merge done\n");

	return 0;
}

