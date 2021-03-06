#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


#define NUM_VALUES 5000000

long *input = NULL;

struct thread_arg
{
	int start;
	int end;
	int seed;
	long ret;
};

long timeval_subtract (
	struct timeval *t1, 
	struct timeval *t2)
{
	return 
		(t1->tv_usec + 1000000 * t1->tv_sec) - 
		(t2->tv_usec + 1000000 * t2->tv_sec);
}

double generation (int* seed)
{
	int i = 0;
	double ret;
	for (i = 0; i < 5; i++) {
		ret += rand_r (seed);
	}
	return ret;

}

double computation (double input)
{
	int i = 0;
	double ret = input;
	for (i = 0; i < 2; i++) {
		ret = sqrt (ret);
	}
	return ret;
}

void* threadgen(void* arg)
{
	struct thread_arg *targ = (struct thread_arg*)arg;
	int i;

	for(i = targ->start; i < targ->end; i++){
		input[i] = generation(&targ->seed);
	}
	
}

void* threadcom(void* arg)
{
	struct thread_arg *targ = (struct thread_arg*)arg;
	int i;
	double result = 0.0;

	for(i = targ->start; i < targ->end; i++){
		result += computation ((double)input[i]);
	}	

	pthread_exit((void*)&result);

}

double run_test (long num_threads, long* gentime, long* cmptime)
{
	struct thread_arg targ[num_threads];
	int cnt=0, length=NUM_VALUES/(int)num_threads;
	pthread_t pid[num_threads];

	struct timeval begin, end, elapsed;
	long etime;
	double result = 0.0;
	void* tmp;
	int i;
	int seed;

	/* STEP1: create a buffer */
	input = (long*)malloc (NUM_VALUES * sizeof (long));

	// create thread arg
	//printf("length: %d\n",length);
	for(i=0; cnt<num_threads; i=i+length){
		targ[cnt++].start = i;
	}	
	for(i=0; i<cnt-1; i++){
		targ[i].end = targ[i+1].start;
	}
	targ[num_threads-1].end = NUM_VALUES;
	//printf("length: %d\n", length);
	for(i=0; i<num_threads; i++){
		pid[i] = i;
		targ[i].ret = 0.0;
	}

	/* STEP1: get some random values */
	gettimeofday (&begin, NULL);

	//seed = 0; /* it must be a thread id (0, 1, .. N-1 if there are N threads) */
	//srand (seed);
	

	for(i=0; i<num_threads; i++){
		targ[i].seed=0; srand(targ[i].seed);
		//printf("gen create %d\n", i);
		pthread_create( &pid[i], NULL, threadgen, (void *)&targ[i]);
	}
	for(i=0; i<num_threads; i++){
		//printf("gen join %d\n", i);
		pthread_join( pid[i], NULL);
	}		
	gettimeofday (&end, NULL);
	*gentime = timeval_subtract (&end, &begin);

	//printf("input[%d]: %ld\n",0,input[0]);
	//printf("input[%d]: %ld\n",NUM_VALUES-1 ,input[NUM_VALUES-1]);

	/* STEP2: run computation using threads */
	gettimeofday (&begin, NULL);
	for(i=0; i<num_threads; i++){
		//printf("com create %d\n", i);
		pthread_create( &pid[i], NULL, threadcom, (void *)&targ[i]);
	}
	for(i=0; i<num_threads; i++){
		//printf("com join %d\n", i);
		pthread_join( pid[i], &tmp);
		result += *(double *) tmp;
	}
	/*
	for (i = 0; i < NUM_VALUES; i++) {
		result += computation ((double)input[i]);
	}*/

	/* STEP3: get elapsed time */
	gettimeofday (&end, NULL);
	*cmptime = timeval_subtract (&end, &begin);

	free (input);

	return result;
}
/*
double run_test (long num_threads, long* gentime, long* cmptime)
{
	struct timeval begin, end, elapsed;
	struct thread_arg targ[num_threads];
	int cnt=0, length=NUM_VALUES/(int)num_threads;

	long etime, *input = NULL;
	double result = 0.0;
	int i;
	int seed;
	int pid[NUM_VALUES];

	// create a buffer
	input = (long *)malloc(NUM_VALUES * sizeof(long));
	
	
	printf("length: %d\n",length);
	for(i=0; cnt<length; i=i+length){
		targ[cnt++].start = i;
	}	
	for(i=0; i<cnt-1; i++){
		targ[i].end = targ[i+1].start-1;
	}
	targ[num_threads-1].end = NUM_VALUES;

	for(i=0; i<cnt; i++){
		printf("start: %d, end: %d\n",targ[i].start, targ[i].end);
	}
	
	for(i=0; i<NUM_VALUES; i++)
		pid[i] = i;
	
	gettimeofday (&begin, NULL);
	
	for(i=0; i<NUM_VALUES; i++){
		pthread_create( &pid[i], NULL, threadgen, NULL );
	}
	for(i=0; i<NUM_VALUES; i++){
		pthread_join( pid[i], NULL);
	}
	
	gettimeofday (&end, NULL);
	*gentime = timeval_subtract (&end, &begin);

	// run computation using threads	
	gettimeofday (&begin, NULL);
	
	for(i=0; i<NUM_VALUES; i++){
		pthread_create( &pid[i], NULL, threadcom, NULL);
	}
	for(i=0; i<NUM_VALUES; i++){
		pthread_join( pid[i], NULL);
	}
	
	gettimeofday (&end, NULL);
	*cmptime = timeval_subtract (&end, &begin);
	
	free(input);
	
	return result;
}

*/
int main (int argc, char *argv[])
{

#define TEST_RUNS	20

	long i = 0, num_threads = 0;
	long gentime = 0, cmptime = 0, tottime = 0;
	long acc_gentime = 0, acc_cmptime = 0;
	double result_old = 0.0, result = 0.0;

	if (argc != 2) {
		printf ("usage: prog1 [# of threads]\n");
		exit (-1);
	}
	num_threads = atoi (argv[1]);

	srand (42);

	/* perform tests */
	for (i = 0; i < TEST_RUNS; i++) {
		result = run_test (num_threads, &gentime, &cmptime);
		if (result_old != 0.0 && result_old != result) {
			printf ("oops! data mismatch occurs: %e %e\n", result_old, result);
			exit (-1);
		} else {
			result_old = result;
		}
		acc_gentime += gentime;
		acc_cmptime += cmptime;
	}

	/* display elapsed times */
	acc_gentime /= TEST_RUNS;
	acc_cmptime /= TEST_RUNS;
	tottime = acc_gentime + acc_cmptime;

	printf ("result = %e\n", result);
	printf ("gentime (sec) = %ld.%06ld\n", acc_gentime/1000000, acc_gentime%1000000);
	printf ("cmptime (sec) = %ld.%06ld\n", acc_cmptime/1000000, acc_cmptime%1000000);
	printf ("tottime (sec) = %ld.%06ld\n", tottime/1000000, tottime%1000000);
}

