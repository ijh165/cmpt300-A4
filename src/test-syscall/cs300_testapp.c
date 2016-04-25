#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>
#include <sys/syscall.h>

#define _CS300_TEST_ 330
#define _ARRAY_STATS_TEST_ 331
#define _PROCESS_ANCESTORS_TEST_ 332
#define ANCESTOR_NAME_LEN 16

typedef struct array_stats
{
	long min;
	long max;
	long sum;
} array_stats_t;

typedef struct process_info
{
	long pid; /* Process ID */
	char name[ANCESTOR_NAME_LEN]; /* Program name of process */
	long state; /* Current process state */
	long uid; /* User ID of process owner */
	long nvcsw; /* # voluntary context switches */
	long nivcsw; /* # involuntary context switches */
	long num_children; /* # children process has */
	long num_siblings; /* # sibling process has */
} process_info_t;

void test_array_stats()
{
	printf("Testing array_stats syscall...\n\n");

	//vars
	const long INVALID_SIZE = (rand()%1000)*(-1);
	const long VALID_SIZE = 10;
	long valid_data[VALID_SIZE];
	valid_data[0] = 2;
	valid_data[1] = -1;
	valid_data[2] = 10;
	valid_data[3] = 6;
	valid_data[4] = 9;
	valid_data[5] = 5;
	valid_data[6] = 21;
	valid_data[7] = 4;
	valid_data[8] = 7;
	valid_data[9] = 3;
	array_stats_t stats;

	printf("INVALID_SIZE: %li\n\n", INVALID_SIZE);

	//valid...
	int result = syscall(_ARRAY_STATS_TEST_, &stats, valid_data, VALID_SIZE);
	assert(stats.min == -1);
	assert(stats.max == 21);
	assert(stats.sum == 66);
	assert(result == 0);

	//invalid...
	result = syscall(_ARRAY_STATS_TEST_, &stats, valid_data, INVALID_SIZE);
	assert(result == -1);
	assert(errno == EINVAL);
	result = syscall(_ARRAY_STATS_TEST_, NULL, valid_data, VALID_SIZE);
	assert(result == -1);
	assert(errno == EFAULT);
	result = syscall(_ARRAY_STATS_TEST_, &stats, NULL, VALID_SIZE);
	assert(result == -1);
	assert(errno == EFAULT);

	printf("\narray_stats test complete!\n\n");
}

void test_process_ancestors()
{
	printf("Testing process_ancestors syscall...\n\n");

	//vars
	const long INVALID_SIZE = (rand()%1000)*(-1);
	const long VALID_SIZE = rand()%1000 + 1;
	process_info_t arr[VALID_SIZE];
	long num_filled;

	printf("INVALID_SIZE: %li\n", INVALID_SIZE);
	printf("VALID_SIZE: %li\n\n", VALID_SIZE);

	//valid...
	int result = syscall(_PROCESS_ANCESTORS_TEST_, arr, VALID_SIZE, &num_filled);
	printf("\n");
	for(int i=0; i<num_filled; i++) {
		printf("arr[%d]: ", i);
		printf("pid: %li, name: %s, state: %li, uid: %li, nvcsw: %li, nivscw: %li, num_children: %li, num_siblings: %li\n",
			arr[i].pid, arr[i].name, arr[i].state, arr[i].uid, arr[i].nvcsw, arr[i].nivcsw, arr[i].num_children, arr[i].num_siblings);
	}
	printf("\n");
	assert(result == 0);
	assert(num_filled <= VALID_SIZE);

	//invalid...
	result = syscall(_PROCESS_ANCESTORS_TEST_, arr, INVALID_SIZE, &num_filled);
	assert(result == -1);
	assert(errno == EINVAL);
	result = syscall(_PROCESS_ANCESTORS_TEST_, arr, VALID_SIZE, NULL);
	assert(result == -1);
	assert(errno == EFAULT);
	result = syscall(_PROCESS_ANCESTORS_TEST_, NULL, VALID_SIZE, &num_filled);
	assert(result == -1);
	assert(errno == EFAULT);

	printf("\nprocess_ancestors test complete!\n\n");
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	printf("Testing syscalls...\n\n");

	test_array_stats();

	test_process_ancestors();

	printf("All tests passed!\n");
	
	return 0;
}