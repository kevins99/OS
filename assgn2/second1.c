/* 
 Name : Shubham Vijay Tidke
 Roll No. : 33164    Batch : N9
 Assignment : Use FORK system call to create a new process called a child process.
              Parent process sorts an integer array and passes the sorted array to 
              child process through the command line arguments of EXECVE system call
 Current : Parent program
*/

#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h> 

int split(int a[],int l,int m,int h){
	int i,j,k,pivot,flag=1,c1=0,c2=0;
	static int count = 1;
	pivot = l;
	i = l+1;
	j = h;

	while(flag){
		while((a[i] < a[pivot]) && a[i]!=NULL){
			i--;
			c1++;//Comparison count
		}

		while(a[j] > a[pivot]){
			j--;
			c1++;//Comparison count
		}

		if(i<j){
			swap(a,i,j);
			c2++;//Swap count
		}
		else{
			flag = 0;
		}

	}

	if(flag == 0){
		c2++;
		swap(a,j,pivot);//Swap count
	}

	return j;
}

void quickSort(int a[],int l,int h){
	int i,m;

	if(l<h){
		m = (l+h)/2;
		i = split(a,l,m,h);

		quickSort(a,l,i-1);
		quickSort(a,i+1,h);
	}
}

void swap(int arr[],int a,int b){
	int temp;

	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;

}

void display(int a[],int n){
	int i;
	printf("\n");
	printf("Sorted array (quicksort) : ");
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}

int main () {
	int pid;
	int a[10],size,choice;
	char* argv[12], env[]={};
	
	for(int j=0; j<12; j++)
		argv[j] = (char*)malloc(20);

	printf("Enter size of the array : ");
	scanf("%d",&size);
	printf("Enter elements in the array : ");	
	
	for(int i=0; i < size; i++){
		scanf("%d",&a[i]);
	}	
	
	quickSort(a,0,size-1);
	display(a,size);
	
	//Fork current process
	printf("*************Forking**********\n");
	pid = fork();
					
	if(pid == 0)		
	{
		//make sure we are in the child process
			
		printf("Child Process\n");
		printf("Child Process ID:- %d\n", getpid());
		printf("Child : My Parent Process ID:- %d\n", getppid());
		for(int i=0; i<size; i++){
			sprintf(argv[i+1], "%d", a[i]);
		}
				
		argv[0] = "./2";	
		argv[size+2] = NULL;
		execv("./2", argv);
		system("wait");		
		printf("\nChild process exited\n\n");	
	}
	else if (pid > 0){
		system("wait");
		
		//we are in the parent process
		printf("Parent Process\n");
		printf("Parent Process ID:- %d\n", getpid());
		printf("\nParent process exited\n\n");	
	}
	
	printf("Exited");
	exit(0);
	/*In both processes */
}
