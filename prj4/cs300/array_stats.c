#include "array_stats.h"
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/errno.h>

asmlinkage long sys_array_stats(struct array_stats* stats, long data[], long size)
{
	struct array_stats tmp_stats;
	long i = 0;	
	long tmp = 0;

	if(size <= 0) {
		return -EINVAL;
	}
	
	if(!stats) {
		return -EFAULT;
	}

	if(copy_from_user(&tmp, &data[0], sizeof(long))) {
		return -EFAULT;
	}
	
	tmp_stats.sum = tmp_stats.min = tmp_stats.max = tmp;
	
	for(i=1; i<size; i++) {
		if(copy_from_user(&tmp, &data[i], sizeof(long))) {
			return -EFAULT;
		}
		if(tmp > tmp_stats.max){
			tmp_stats.max = tmp;
		}
		else if(tmp < tmp_stats.min){
			tmp_stats.min = tmp;
		}
		tmp_stats.sum += tmp;
	}

	if (copy_to_user(&(stats->sum), &(tmp_stats.sum), sizeof(long)) ||
		copy_to_user(&(stats->min), &(tmp_stats.min), sizeof(long)) ||
		copy_to_user(&(stats->max), &(tmp_stats.max), sizeof(long)))
	{
		return -EFAULT;
	}

	printk("Min:%li Max:%li Sum:%li\n", stats->min, stats->max, stats->sum);
	
	return 0;		 
}