/* 
 Name : Shubham Vijay Tidke
 Roll No. : 33164    Batch : N9
 Assignment : Use FORK system call to create a new process called a child process.
              Parent process sorts an integer array and passes the sorted array to 
              child process through the command line arguments of EXECVE system call
 Current : Child program
*/

#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h> 

int Binary(long a[],int n,int key){
	int low,high,mid,i=0;

	low=0;
	high=n-1;

	while(low<=high){
		mid=(low+high)/2;
		i += 1;

		if(key==a[mid]){
			return mid;
		}

		if(key<a[mid]){
			high=mid-1;
		}
		else{
			low=mid+1;
		}

	}

	printf("Key %ld is not present in the array!!!\n", key);
	return 0;
}

void main(int argc, char *argv[],char *envp[]){

	long a[12],key,ans;	
	int n=0;

	for(int i=1; argv[i] != NULL; i++){
		a[i-1] = strtol(argv[i], NULL, 12);
		n++;	
	}
	
	printf("In second child process. My process-id is %d.\n", getpid());
	printf("My parent's process-id is %d.\n\n", getppid());
	
	// take input of value to search
	printf("\nEnter the value to be search:- ");
	scanf("%ld",&key);
	printf("Applying Binary Search...\n");
	ans = Binary(a,n,key);
	
	if(ans != 0)
		printf("Key %ld is present at the position %d!!!\n", key, ans);
	else
		printf("Key not found !!\n");

	return 0;
}
