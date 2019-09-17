#include<stdio.h> 
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

void accept()
{
        int array[10];
        int i,n;
        printf("Enter the number of elements you want to sort:\n");
        scanf("%d",&n);
        printf("test\n");
        
        for(i=0;i<n;i++)
        {
                scanf("%d",&array[i]);
        }
        
        for(i=0;i<n;i++)
        {
                printf("%d",array[i]);
        }
}

int main (int argc,char **argv)
{
        char *arg[] = {"./2",NULL};
        char *env[] = {NULL};
                
        pid_t pid;        
        
        pid=fork();
        
        if(pid==0)
        {
                accept();
                printf("\nIn the Child Process!\n");
                printf("Child Process ID: %d\n",getpid());
                printf("Parent ID of this process: %d\n",getppid());
                execve("./2",arg,env);
        }
        
        else if(pid>0)
        {
                system("wait");
                sleep(5);
                printf("In the Parent Process!\n");
                printf("Parent Process ID: %d\n",getpid());
                
        }
        
        else
        {
                printf("Error in Forking!");
        }                                
}
