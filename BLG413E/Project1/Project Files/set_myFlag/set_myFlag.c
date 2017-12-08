#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage long set_myFlag(pid_t pid, int value) {
	
	if ((current->cred)->uid == 0) {
		struct task_struct *tsk;
		tsk = find_task_by_vpid(pid);
		if (tsk != NULL) {
			if (value == 0 || value == 1){
				tsk->myFlag = value;
			} else {
				return -EBADMSG;
			}
		} else {
			return -ESRCH;
		}
	} else {
		return -EACCES;
	}
	return 0;
}
