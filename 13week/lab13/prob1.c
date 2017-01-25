#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


#define NUM_VALUES 5000000


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

double run_test (long num_threads, long* gentime, long* cmptime)
{
	struct timeval begin, end, elapsed;
	long etime, *input = NULL;
	double result = 0.0;
	int i;
	int seed;

	/* STEP1: create a buffer */
	input = (long*)malloc (NUM_VALUES * sizeof (long));


	/* STEP1: get some random values */
	gettimeofday (&begin, NULL);

	seed = 0; /* it must be a thread id (0, 1, .. N-1 if there are N threads) */
	srand (seed);
	for (i = 0; i < NUM_VALUES; i++) {
		input[i] = generation (&seed);
	}
	gettimeofday (&end, NULL);
	*gentime = timeval_subtract (&end, &begin);


	/* STEP2: run computation using threads */
	gettimeofday (&begin, NULL);
	for (i = 0; i < NUM_VALUES; i++) {
		result += computation ((double)input[i]);
	}

	/* STEP3: get elapsed time */
	gettimeofday (&end, NULL);
	*cmptime = timeval_subtract (&end, &begin);

	free (input);

	return result;
}

int main (int argc, char *argv[])
{

#define TEST_RUNS	20

	long i = 0, num_threads = 0;
	long gentime = 0, cmptime = 0, tottime = 0;
	long acc_gentime = 0, acc_cmptime = 0;
	double result_old = 0.0, result = 0.0;

	num_threads = 1;

	srand (42);

	/* perform tests */
	for (i = 0; i < TEST_RUNS; i++) {
		result = run_test (num_threads, &gentime, &cmptime);
		if (result_old != 0.0 && result_old != result) {
			printf ("oops! data mismatch occurs\n");
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

