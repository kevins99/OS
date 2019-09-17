#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int mat1[10][10];
int mat2[10][10];
int mat3[10][10];

int r1, c1, r2, c2 

void *mult(void *);

int main(void)
{
	pthread_t tid;
	int i, j, k;
	
	printf("Enter number of rows for matrix 1");
	scanf("%d", &r1);
	
	printf("Enter number of columns for matrix 1");
	scanf("%d", &c1);
	
	printf("Enter number of rows for matrix 2");
	scanf("%d", &r2);
	
	printf("Enter number of columns for matrix 2");
	scanf("%d", &c2);
	
	for(i=0;i<r1;i++)
    	{
        	for(j=0;j<c1;j++)
		{
		    printf("Enter Mat1[%d][%d] :",i,j);
		    scanf("%d",&mat1[i][j]);
		}
    	}
    	
    	for(i=0;i<r2;i++)
    	{
        	for(j=0;j<c2;j++)
		{
		    printf("Enter Mat2[%d][%d] :",i,j);
		    scanf("%d",&mat2[i][j]);
		}
    	}
}
