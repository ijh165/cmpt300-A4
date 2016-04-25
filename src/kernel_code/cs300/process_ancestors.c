#include "process_ancestors.h"
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <asm/uaccess.h>
#include <asm/errno.h>

asmlinkage long sys_process_ancestors(struct process_info info_array[], long size, long* num_filled)
{
	struct task_struct* curr_task = current;

	long tmp_num_filled = 0;
	long children_count = 0;
	long sibling_count = 0;
	struct list_head* pos = NULL;

	if (size <= 0) {
		return -EINVAL;
	}

	if (!num_filled) {
		return -EFAULT;
	}

	while (curr_task->parent != curr_task)
	{
		if (tmp_num_filled > 0) {
			curr_task = curr_task->parent;
		}

		//count num of children
		children_count = 0;
		list_for_each(pos, &(curr_task->children)) {
			children_count++;
		}
		
		//count num of siblings
		sibling_count = 0;
		list_for_each(pos, &(curr_task->sibling)) {
			sibling_count++;
		}

		printk("pid: %li, name: %s, state: %li, uid: %li, nvcsw: %li, nivscw: %li, num_children: %li, num_siblings: %li\n",
			(long) curr_task->pid, curr_task->comm, curr_task->state, (long) (curr_task->cred)->uid.val, curr_task->nvcsw, curr_task->nivcsw, children_count, sibling_count);
		
		//store into info_array
		if (tmp_num_filled < size) {
			//create new process_info struct
			struct process_info item;
			//store the info into the struct
			item.pid = (long) curr_task->pid;
			strcpy(item.name, curr_task->comm);
			item.state = curr_task->state;
			item.uid = (long) (curr_task->cred)->uid.val;
			item.nvcsw = curr_task->nvcsw;
			item.nivcsw = curr_task->nivcsw;
			item.num_children = children_count;
			item.num_siblings = sibling_count;
			//add the struct to info_array
			if(copy_to_user(&info_array[tmp_num_filled], &item, sizeof(struct process_info))) {
				return -EFAULT;
			}
			//incr tmp_num_filled
			tmp_num_filled++;
		}
	}

	if (copy_to_user(num_filled, &tmp_num_filled, sizeof(long))) {
		return -EFAULT;
	}
	
	return 0;
}