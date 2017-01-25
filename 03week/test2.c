#include <stdio.h>

int main(void){
	int i,j;

	for(i=1;i<10;i++){
		if(i%2==0)
			for(j=1;j<10;j++){
				if(i<j)
					continue;
				printf("%d*%d=%d\n",i,j,i*j);
			}
	}
	return 0;
}
