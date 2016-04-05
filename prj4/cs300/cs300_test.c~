#include <linux/kernel.h>

asmlinkage long sys_cs300_test(int argument){
	long result = 0;
	
	printk("Hello World!\n");
	printk("--syscall argument %d\n");
	
	result = argument +1;
	printk("--returning %d + 1= %ld\n", argument, result);
	
	return result;
}
