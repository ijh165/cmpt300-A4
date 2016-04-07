#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <asm/errno.h>

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

int main(int argc, char *argv[])
{
	printf("\nDiving to kernel level\n\n");

	//testing cs300_test.c
	/*int result = syscall(_CS300_TEST_, 999);*/

	//testing array_stats.c
	/*array_stats_t stats;
	long data[10] = {2,-1,10,6,9,5,21,4,7,3};
	int result = syscall(_ARRAY_STATS_TEST_, &stats, data, 10);
	printf("Min: %ld\n", stats.min);
	printf("Max: %ld\n", stats.max);
	printf("Sum: %ld\n", stats.sum);*/

	//testing process_ancestors.c
	const int ARR_SIZE = 10;
	process_info_t arr[ARR_SIZE];
	long num_filled = 0;
	int result = syscall(_PROCESS_ANCESTORS_TEST_, arr, ARR_SIZE, &num_filled);
	printf("\n");
	for(int i=0; i<num_filled; i++) {
		printf("=== arr[%d] ===\n", i);
		printf("pid: %li, name: %s, state: %li, uid: %li, nvcsw: %li, nivscw: %li, num_children: %li, num_siblings: %li\n",
			arr[i].pid, arr[i].name, arr[i].state, arr[i].uid, arr[i].nvcsw, arr[i].nivcsw, arr[i].num_children, arr[i].num_siblings);
	}
	printf("\nnum_filled: %li\n", num_filled);

	printf("\nRising to user level w/ result = %d\n\n", result);
	
	return 0;
}