#include <asm/errno.h>
#include <linux/kernel.h>
#include "array_stats.h"
#include <asm/uaccess.h>
//#include </usr/include/stdlib.h>

struct array_statz{
	long min;
	long max;
	long sum;
};
asmlinkage long sys_array_stats(struct array_stats *stats, long data[], long size){
	struct array_statz structure;
	long i = 0; 
	long tmp = 0;
	long tmp1 = 0;
	long tmp2 = 0;
	if(size < 0){
		return -EINVAL;
	}
	else if(!stats){
		return -EFAULT;
	}
	else{
		if(copy_from_user(&data[0], &tmp, sizeof(long))){
			return -EFAULT;
		}
		structure.sum = structure.min = structure.max = tmp;
			
		for(i =1; i<size; i++){
			if(copy_from_user(&data[i], &tmp, sizeof(long))){
				return -EFAULT;
			}
			if(tmp > structure.max){
				structure.max = tmp;
			}
			else if(tmp < structure.min){
				structure.min = tmp;
			}
			structure.sum += tmp;
		}
		
		if(copy_to_user(&(structure.max), &tmp1, sizeof(long)) || copy_to_user(&(structure.min), &tmp2, sizeof(long)) || copy_to_user(&(structure.sum), &tmp2, sizeof(long))){
		return -EFAULT;
		}
		stats->min = tmp;
		stats->max = tmp1;
		stats->sum = tmp2;
		return 0;
	} 		 
}
