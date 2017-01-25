#include <stdio.h>
#include <signal.h>

int beeps = 0;

void handler(int sig){
	printf("BEEP\n");

	if(++beeps < 5)
		alarm(1);
	else{
		printf("BOOM!\n");
		exit(0);
	}
}

main() {
	signal(SIGALRM, handler);
	alarm(1);

	while(1){
	}
}
