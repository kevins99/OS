#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int pid;
	printf("Fork process");
	int ppid = getppid();
	
	pid = fork();
	if (pid != 0)
	{
		printf("\n\nParent process started\n\n");
		printf("\n\nParent process id:: %d\n\n",getpid());
		printf("\n\bBash id(Parent's parent's id):: %d\n\n",getppid());
		exit(0);
		printf("\nAfter sleep\n\n");		
	}
	{
		//CHILD ID OBTAINED IN CHILD PROCESS BY 'getpid()'
		//PARENT ID OBTAINED IN CHILD PROCESS BY 'getppid()'
		printf("\nChild id::%d\n\n",getpid());
		printf("\nParent id::%d\n\n",getppid());		
		sleep(15);
		wait(NULL);
		printf("\n\nParent process completed\n\n");
		printf("\nID::%d",getpid());
		printf("\nparent ID::%d",getppid());
	}
	return 0;
}
