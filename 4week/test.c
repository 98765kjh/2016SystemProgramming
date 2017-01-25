#include <stdio.h>

typedef unsigned char *pointer;


void displayHex(pointer start, int len){
	int i;
	for(i=0; i<len; i++)
	{
		printf("%.2x\t",start[i]);
	}
	printf("\n");
}

void displayBin(pointer start,int len){
	int i, j;
	int b=128;

	for(i=0; i<len; i++)
	{
		for(j=0; j<8 ; j++)
		{
			//printf("%d", start[i]&b);
			if((start[i]<<j)&b)
				printf("1");
			else
				printf("0");
			
			if(j==3 || j==7)
				printf(" ");
		}	
		
	}
	printf("\n");
}

void lsb_msb(pointer start,int len){
	int i, j;
	int b=128;
	printf("MSB : ");
	for(i=0 ; i<4 ; i++)
	{
		if((start[0]<<i)&b)
			printf("1");
		else
			printf("0");
	}
	printf("\tLSB : ");
	for(i=0 ; i<4 ; i++)
	{
		if((start[3]<<i)&b)
			printf("1");
		else
			printf("0");
	}
	printf("\n");	
}
unsigned int inverse_bit(pointer start,int len){
	int i, j;
	int b=1;
	for(i=3 ; i>=0 ; i--)
	{
		for(j=0;j<8;j++)
		{
			if((start[i]>>j)&b)
				printf("1");
			else
				printf("0");
			if(j==3||j==7)
				printf(" ");
		}
	}
	printf("\n");	
}

int swap (int* x, int* y){
	int c=(*x)^(*y);
	*x = c^(*x);
	*y = c^(*y);
}

int partial_multi (int x, int y)
{
	x = x&15;
	y = y&4095;
	y=y>>8;

	return x*y;
}

void main(int argc, char** argv)
{
	int a = 14213;	
	int b = 19352;	
		
	printf("\n---dispaly Decimal---\n");
	printf("int a = %d\n", a);
	printf("int b = %d\n", b);

	printf("\n---1. dispaly Hex---\n");
	displayHex((pointer) &a , sizeof(int));
	displayHex((pointer) &b , sizeof(int));

	printf("\n---2. dispaly Binary---\n");	
	displayBin((pointer) &a , sizeof(int));	
	displayBin((pointer) &b , sizeof(int));	

	printf("\n---3. print LBS/MBS---\n");
	lsb_msb((pointer) &a , sizeof(int));
	lsb_msb((pointer) &b , sizeof(int));

	printf("\n---4. Inverse value---\n");
	inverse_bit((pointer) &a , sizeof(int));
	inverse_bit((pointer) &b , sizeof(int));

	printf("\n---5. partial Multiplication---\n");
	printf ("%d\n", partial_multi (a, b));

	printf("\n---6. swap 연산---\n");
	printf("a=%d, b=%d\n",a,b);
	swap(&a,&b);
	printf("a=%d, b=%d\n",a,b);		
}
