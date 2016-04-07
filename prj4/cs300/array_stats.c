#include <asm/errno.h>
#include <linux/kernel.h>
#include "array_stats.h"
#include <asm/uaccess.h>
//#include </usr/include/stdlib.h>


asmlinkage long sys_array_stats(struct array_stats *stats, long data[], long size){

	struct array_stats statz;
		long i = 0;	
		long tmp = 0;

	if(size <= 0) { return -EINVAL; } 
	if(!stats) { return -EFAULT; } 

		if(copy_from_user(&tmp, &data[0], sizeof(long))){
			return -EFAULT;
		}
		else{
			statz.sum = statz.min = statz.max = tmp;
			printk(KERN_NOTICE "Sum=min=max = %li\n", tmp);
		}
	for(i =1; i<size; i++){
		if(copy_from_user(&tmp, &data[i], sizeof(long))){
				return -EFAULT;
			}
		if(tmp > statz.max){
			statz.max = tmp;
		}
		else if(tmp < statz.min){
			statz.min = tmp;
		}
		statz.sum += tmp;
	}

	if(copy_to_user(&(stats->sum), &(statz.sum), sizeof(long)) || copy_to_user(&(stats->min), &(statz.min), sizeof(long)) || copy_to_user(&(stats->max), &(statz.max), sizeof(long))){
		return -EFAULT;
	}
	return 0;
		 
}
