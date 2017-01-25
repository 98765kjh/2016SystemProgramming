#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

#include "compute.h"

#define segfault 11
#define arithfault 8
#define _try\
	{\
		if(!(ret=sigsetjmp(buf, 1))){

#define _catch(type)\
	 }else if(ret==type) {\

#define _throw(type)\
	siglongjmp(buf, type)

#define _etry\
	}}

sigjmp_buf buf;

void sig_handler(int sig)
{
	_throw(sig);
}
/*void flot_handler(int sig)
{
	_throw(sig);
}
*/

int run_compute (char* fname, int (*fn) (void))
{
	int ret;
	
	_try {
		printf ("\n--------------------------------\n");
		printf ("%s begins\n", fname);
		/*if(ret=sigsetjmp(buf, 1))
		{
			if(ret==11){ _throw(segfault); }
			else if(ret==8){ _throw(arithfault); }
		}*/
		ret = fn ();	
		printf ("%s returns %d\n", fname, ret);
		printf ("%s done\n", fname);
	} _catch (segfault) {
		printf ("caught a segmentation fault\n");
	} _catch (arithfault) {
		printf ("caught an arithmetic fault\n");
	}
	_etry

	return ret;
}

int main (int argc, char** argv)
{
	signal(SIGSEGV, sig_handler);
	signal(SIGFPE, sig_handler);

	run_compute ("compute1()", compute1);
	run_compute ("compute2()", compute2);
	run_compute ("compute3()", compute3);
	run_compute ("compute4()", compute4);
	run_compute ("compute5()", compute5);

	return 0;
}

