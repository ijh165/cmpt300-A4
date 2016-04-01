#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fibonacci(void* args) {
	long long* size_ptr = (long long*) args;
	long long N = *size_ptr;
	free(args);

	// Setting up initial array
	long long* fibonacci_results = (long long*)malloc(N*sizeof(long long));

	if (N >= 1) {
		fibonacci_results[0] = 0;
	}

	if (N >= 2) {
		fibonacci_results[1] = 1;
	}

	if (N >= 3) {
		for(long long i = 2; i < N; i++) {
			fibonacci_results[i] = fibonacci_results[i-1] + fibonacci_results[i-2];
		}
	}

	// Return fibonacci_results
	pthread_exit((void*) fibonacci_results);

}

int main(int argc, char **argv) {
	if (argc < 2 || argc > 2) {
		perror("No arguments or too many arguments, exiting program");
		exit(0);
	}

	if (atoll(argv[1]) < 0) {
		perror("Invalid argument, exiting program");
		exit(0);
	}

	long long *N = malloc(sizeof(*N));
	*N = atoll(argv[1]);

	// Thread ID;
	pthread_t tid;

	// Create attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, fibonacci, N);

	// Wait until thread is done its work
	long long *results;
	pthread_join(tid, (void**)&results);

	for(long long i = 0; i < atoll(argv[1]); i++) {
		printf("%lld, ", results[i]);
	}

	printf("\n");
	free(results);

	return 0;
}
