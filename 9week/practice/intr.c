#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig){
	printf("You think hitting ctrl-c will stop the bomb?\n");
	sleep(2);
	printf("Well...");
	sleep(1);
	printf("OK\n");
	exit(0);
}

main(){
	signal(SIGINT, handler);
	while(1){
	}
}
