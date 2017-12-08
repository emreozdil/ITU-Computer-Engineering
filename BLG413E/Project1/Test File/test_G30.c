#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>

#define setMyFlag 355

int main(){
	int flag, pid, p_priority;

	printf("Process PID: %d\n", getpid());
	
	printf("PID: ");
	scanf("%d", &pid);

	printf("myFlag: ");
	scanf("%d", &flag);

	int errorNumber = syscall(setMyFlag, pid, flag);
	
	if(errno == 0) {
		printf("Successfully set flag\n");
		printf("exit.c test\n");
	}
	else if(errno == EACCES) {
		printf("Error: EACCES\nUse 'sudo'\n");
		return 0;
	}
	else if(errno == ESRCH) {
		printf("Error: ESRCH\n%d pid process not found\n", pid);
		return 0;
	}
	else if(errno == EBADMSG) {
		printf("Error: EBADMSG\nFlag must be 0 or 1\n");
		return 0;
	}
	
	int index;
	pid_t forkpid;

	for(index = 0; index < 3; index++){
		forkpid = fork();
		if(forkpid == 0){
			break;
		}
	}
	if(forkpid == -1){
		printf("Fork failed\n");
	} else if (forkpid == 0){
		printf("Child PID: %d Parent PID: %d\n", getpid(), getppid());
		while(1);
	} else {
		printf("Parent PID: %d\n", getpid());
		getchar();
		getchar();
		printf("Parent die\n");
		exit(0);
	}
	return 0;
}
