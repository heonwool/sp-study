/**
  * Quiz 1:
  * Make the result be 10000 using mutex
  *
  **/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

int counter = 0;
#define NUM_THREAD 10000

pthread_mutex_t lock;

void * thr_main(void *arg) {
//	printf("thread %d start \n", (int)(intptr_t)arg);
	pthread_mutex_lock(&lock);

	counter++;
//	sleep(1);

	pthread_mutex_unlock(&lock);
	return ((void *)1);
}

int main(void) {
	int err, i;
	pthread_t tid[NUM_THREAD];
	void *tret;

	for(i = 0; i < NUM_THREAD; i++) {
		err = pthread_create(&tid[i], NULL, thr_main, (void *)((intptr_t)i));
		if (err != 0) exit(1);
	}

	for(i = 0; i < NUM_THREAD; i++) {
		err = pthread_join(tid[i], &tret);
		if (err != 0) exit(2);
	}

	printf("done %d!\n", counter);

	pthread_mutex_destroy(&lock);

	return 0;
}
