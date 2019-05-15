#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct thread_data {
	int n;
	int result;
} thread_data;

/* Inefficiently, compute successive prime numbers.
   Return the nth prime number.  */
void* compute_prime (void * arg) {
	/* dereference the parameter */
	thread_data * tdata = (thread_data *)arg;
	int n = tdata->n;
	int candidate = 2;

	while (true) {
		int factor;
		int is_prime = true;

		/* test primality by successive division.  */
		for (factor = 2; factor < candidate; ++factor)
			if (candidate % factor == 0) {
				is_prime = false;
				break;
			}
		/* is prime number we're looking for?  */
		if (is_prime) {
			if (--n == 0) {
				/* define the result  */
				tdata->result = candidate;
				pthread_exit(NULL);
			}
		}
		++candidate;
	}
}

int main ()
{

	//printf("The second random number  is %d\n", num2);

	pthread_t tid1,tid2,tid3;
	//thread_data tdata;
	thread_data tdata2, tdata3, tdata4;
	time_t t;

	time_t t1, t2;
	srand((unsigned) time(&t1));

	//int num = 1956;
	tdata4.n = 1956;
	tdata2.n = rand() % 5000;
	tdata3.n = rand() % 5000;
	printf("i is %d , j is %d\n", tdata2.n, tdata3.n);

	/* intialize random number generator */
	//srand((unsigned) time(&t));
	//tdata.n=rand() % 5000;
	//printf("The %dth prime number\n", tdata.n);

	// printf("check %d",tdata.n );

	//printf("the %dth prime number", num1);

	/* start the thread, up to "tdata.n" */
	pthread_create (&tid1, NULL, compute_prime, (void *)&tdata2);
	pthread_create(&tid2, NULL, compute_prime, (void *)&tdata3);
	pthread_create(&tid3, NULL, compute_prime, (void *)&tdata4);
	/* wait for the thread to complete  */
	pthread_join (tid1, NULL);

	/* print the computed prime */
	//(" is %d.\n", tdata.result);
	printf("pi is %d, pj is %d\n", tdata2.result,tdata3.result);
	//printf(" pj is %d.\n", tdata3.result);
	int product = (tdata2.result*tdata3.result);

	printf("their product is  %d.\n", product);
}
