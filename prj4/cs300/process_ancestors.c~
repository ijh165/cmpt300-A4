#include "process_ancestors.h"
#include <linux/kernel.h>
#include <asm/errno.h>
#include <linux/sched.h>
#include <linux/cred.h>


asmlinkage long sys_process_ancestors(struct process_info info_array[], long size, long *num_filled){
	
	// place for loop to encapsulate entire body below
	struct task_struct *task = current;
	
	//*****************
	// ivan figure out how to count the children and siblings in the circular LL , i keep getting infinte loop
	struct list_head *pos;
	struct list_head children_list;
        struct list_head siblings_list;
	long tmp = 0;
	long tmp2 = 0;
	children_list = task->children;
	siblings_list = task->sibling;
	pos = children_list.next;
	
	while((pos->next)!= &children_list){
		tmp++;
	}
	
	//********************* 


	printk(KERN_NOTICE "pid: %d, state: %s, uid: %li, nvcsw: %li, nivscw: %li, num_children: %li, num_siblings: %li", task->pid, task->comm, (long)(task->cred)->uid.val, task->nvcsw, task->nivcsw, tmp, tmp2);
        // store the stuff in info_array
        
        
        *num_filled++;   
         
    	task = (current->parent);
	
	return 0;
}
