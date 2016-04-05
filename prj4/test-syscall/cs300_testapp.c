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

int main(int argc, char *argv[]){
	printf("\nDiving to kernel level\n\n");
	int result = syscall(_CS300_TEST_, NULL, 5, NULL);
	printf("\nRising to user level w/ result = %d\n\n", result);
	
	return 0;
}


