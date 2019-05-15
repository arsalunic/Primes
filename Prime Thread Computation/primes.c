#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int myResults[2];
int index = 0;

pthread_mutex_t mutexInit = PTHREAD_MUTEX_INITIALIZER;

typedef struct thread_data {
	int n;
} thread_data;

/* Return the nth prime number.  */
void* compute_prime (void * arg) {
	/* dereference the parameter */
	thread_data * tdata = (thread_data *)arg;
	int n = tdata->n;
	int candid = 2;

	while (true) {
		int factor;
		int is_prime = true;

		/* test primarily by division.  */
		for (factor = 2; factor < candid; ++factor)
			if (candid % factor == 0) {
				is_prime = false;
				break;
			}
		/* is prime number we're looking for?  */
		if (is_prime) {
			if (--n == 0) {
				pthread_mutex_lock(&mutexInit);
				myResults[index] = candid;
				index++;

				pthread_mutex_unlock(&mutexInit);
				//critical section ends
				pthread_exit(NULL);
			}
		}

		++candid;
	}
}

int main (){

	pthread_t tid,tid1;
	thread_data tdata2, tdata3;

	srand ( time(NULL) );
	tdata2.n = rand() % 5000;
	tdata3.n = rand() % 5000;
	printf("i is %d , j is %d\n", tdata2.n, tdata3.n); 

	pthread_create (&tid, NULL, compute_prime, (void *)&tdata2);
	pthread_create(&tid1, NULL, compute_prime, (void *)&tdata3);

	pthread_join (tid, NULL);
	pthread_join (tid1, NULL);
	printf("pi is %d, pj is %d\n", myResults[0],myResults[1]);

	int product = (myResults[0]*myResults[1]);
	printf("their product is  %d.\n", product);
}
