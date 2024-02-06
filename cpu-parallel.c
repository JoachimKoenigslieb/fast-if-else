#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 8

typedef struct {
    int threadId;
    int isEven; // This is where the thread will store its result
    int isOdd; // This is where the thread will store its result
    u_int32_t testCase; // This is where the thread will store its result
	u_int32_t maxCheck;
} ThreadData;

void *checkEvenOdd(void *arg) {
	ThreadData *data = (ThreadData *)arg; // derefence all the things...

    for (u_int32_t i = 1 + 2 * data->threadId; i <= data->maxCheck - 2 * NUM_THREADS; i += 2 * NUM_THREADS) {
		// printf("thread %d checking (odd) %d\n", data->threadId, i);
		if (i == data->testCase) {
			data->isOdd = 1;
		}
	}

	// depending on which thread we are, its still possible to skip over this now.
	for (u_int32_t i = 2*data->threadId; i <= data->maxCheck - 2 * NUM_THREADS; i += 2 * NUM_THREADS) {
		// printf("thread %d checking (even) %d\n", data->threadId, i);
		if (i == data->testCase) {
			// checking all the even numbers...
			data->isEven = 1;
		}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	u_int32_t test_case = atoi(argv[1]);
	u_int32_t max_check = atoi(argv[2]);

	int isOdd = 0;
	int isEven = 0;

    pthread_t threads[NUM_THREADS];
	ThreadData data[NUM_THREADS];

    for(int t=0; t<NUM_THREADS; t++){
        data[t].threadId = t;
		data[t].maxCheck = max_check;
		data[t].testCase = test_case;
		data[t].isEven = 0;
		data[t].isOdd = 0;

        int rc = pthread_create(&threads[t], NULL, checkEvenOdd, (void *)&data[t]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

	// Wait for all threads to complete
    for (int t=0; t<NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);

		isEven += data[t].isEven;
		isOdd += data[t].isOdd;
    }


	for (u_int32_t i = data->maxCheck - 2 * NUM_THREADS; i<data->maxCheck; i=i+2) {
		// printf("thread %d checking (odd extra) %d\n", data->threadId, i);
		if (i == data->testCase) {
			isOdd += 1;
		}
	}

	if (test_case == max_check) {
		isOdd += 1;
	}

	// the max value we can have in whatever bit-width is 2**n - 1, this means we WILL skip over this
	for (u_int32_t i = data->maxCheck - 2 * NUM_THREADS - 1; i<(data->maxCheck - 1); i=i+2) {
		// printf("thread %d checking (even extra) %d\n", data->threadId, i);

		if (i == data->testCase) {
			// checking all the even numbers...
			isEven += 1;
		}
	}

	if (test_case == max_check - 1) {
		isEven += 1;
	}

	if (isEven) {
		printf("%d is even!\n", test_case);
	}

	if (isOdd) {
		printf("%d is odd!\n", test_case);
	}

	/* Last thing that main() should do */
    pthread_exit(NULL);

    return 0;
}
