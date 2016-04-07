#include <stdio.h>

#include <unistd.h>
#include <sys/syscall.h>

#define _CS300_TEST_ 332
#define ANCESTOR_NAME_LEN 16
struct process_info {

long pid;
/* Process ID */

char name[ANCESTOR_NAME_LEN];
/* Program name of process */

long state;
/* Current process state */

long uid;
/* User ID of process owner */
long nvcsw;
/* # voluntary context switches */

long nivcsw;
/* # involuntary context switches */

long num_children;
/* # children process has */

long num_siblings;
/* # sibling process has */
};

struct array_stats{
	long min;
	long max;
	long sum;
};

int main(int argc, char *argv[]){
	printf("\nDiving to kernel level\n\n");
	//int result = syscall(_CS300_TEST_, NULL, 5, NULL);

	
		long data[5] = {1, 3, -1, 9, 7};
	struct array_stats stats;
		
	int result = syscall(331, &stats, data, 5);
	printf("\nRising to user level w/ result = %d\n\n", result);
	 
		printf("%li %li %li\n", stats.min, stats.max, stats.sum);
	
	return 0;
}


