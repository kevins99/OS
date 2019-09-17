#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*void mergesort(int [],  int, int)
void merge()

void quicksort(int[], int, int)
int partition(int[], int, int)*/

int main(int argc, char **argv)
{
	char *arg[] = {"./2", NULL} //arguments to be passed to execve  
	char *env = {NULL}
	int arr[30];
	int n;
	
	pid_t pid;
	pid = fork();			//creates a fork process you may use vfork too
	
	if(pid == 0)
	{
		printf("Child process\n");
		printf("Enter the number of elements\n");
		scanf("%d", &n);
	
		for(i=0; i<n; i++)
		{
			scanf("%d", arr[i]);
			printf("Number accepted\n");
		}
	
		printf("Process id is:%d", getpid());
		printf("Parent's pid is %d", getppid());
		execve("./2", arg, env);
	}
	
	else if(pid > 0)
	{
		system("wait");
		sleep(5);				
		printf("Parent\n");
		printf("pid = %d", getpid());
	}
	else 
	{
		printf("Forking unsuccessful");		//-1 returned when unsuccessful
		
	}
	
}

/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
#define MAX 50
 
 
void main(int argc, char *argv[])
{
 int a[20],n,i;
 char *c_array[20];
 pid_t pid;
 int status;
 char *newenviron[]={NULL};
 char *newargv[20];
  printf("Enter element: ");
  scanf("%d",&n);
  char c1[sizeof(int)];
  char* ch;    
  snprintf(c1, sizeof(int), "%d", n); //copy those 4bytes
	ch = malloc(sizeof(c1)); 
	strcpy(ch, c1); // copy to the array of  				results
	printf(" program 1 value of n %s\n", ch);
newargv[0] = argv[1];
newargv[1] = ch; 
//newargv[2]=NULL;
 pid=fork();
 if(pid==-1)
   printf("Error on fork\n");
 
 if(pid==0)
 {
   execve(argv[1], newargv, newenviron);
 
 }
else if(pid>0)
 {
 // sleep(1);
  printf("Parent process\n");
  wait(&status);
}
 
}*/
