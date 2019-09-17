//Assignment 3 : Matrix Multiplication using POSIX Threads
//33165
//Name: Kevin Stephen

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>

int *resMat;

void inputMatrix(int *mat,int rows,int cols){
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			printf("\nEnter (%d,%d): ",i+1,j+1);
			scanf("%d",mat+i*cols+j);
		}
	}
	
}

void displayMatrix(int *mat,int rows,int cols){
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			printf("%d  ",*(mat+i*cols+j));
		}
		printf("\n");
	}
	
}


void *multiplyMatrix(void *d){
	int *data;
	data = (int *)d;
	
	int n = data[0];
	int i = data[1];
	int j = data[2];
	int sum = 0;
	for(int x=3;x<n;x+=2){
		sum = sum + (data[x]*data[x+1]);	
	}	
	
	printf("\nThread for (%d,%d) calculated value: %d",i+1,j+1,sum);

	int *p=(int*)malloc(sizeof(int));
    *p=sum;
	pthread_exit(p);
}


int main(){
	
	int n;
	int *matA,*matB;
	int rowsA,colsA,rowsB,colsB;
	pthread_t *thread;
	int choice,x=1;
	
	while(x){
		printf("\n1.Input Matrices");
		printf("\n2.Display Matrices");
		printf("\n3.Multiply Matrices");
		printf("\n4.Exit");
		printf("\nEnter Choice: ");
		scanf("%d",&choice);
		
		switch(choice){
			case 1:
				printf("\nEnter Number of Rows for matrix A: ");
				scanf("%d",&rowsA);
				printf("\nEnter Number of Columns for matrix A: ");
				scanf("%d",&colsA);
				matA = (int *)malloc(sizeof(int)*rowsA*colsA);
				printf("\nEnter Matrix A: ");
				inputMatrix(matA,rowsA,colsA);

				printf("\nEnter Number of Rows for matrix B: ");
				scanf("%d",&rowsB);
				printf("\nEnter Number of Columns for matrix B: ");
				scanf("%d",&colsB);
				matB = (int *)malloc(sizeof(int)*rowsB*colsB);
				printf("\nEnter Matrix B: ");
				inputMatrix(matB,rowsB,colsB);
				
				
			break;
			
			case 2:
				printf("\nMatrix A: \n");
				displayMatrix(matA,rowsA,colsA);
				
				printf("\nMatrix B: \n");
				displayMatrix(matB,rowsB,colsB);
			break;
			
			case 3:
				if(colsA==rowsB){
					resMat = (int *)malloc(sizeof(int)*rowsA*colsB);
					thread = (pthread_t*)malloc(sizeof(pthread_t)*rowsA*colsB);
					int *data;
					data = (int *)malloc(sizeof(int)*(colsA+rowsB+3));
				
					for(int i=0;i<rowsA;i++){
						for(int j=0;j<colsB;j++){
							data[0] = colsA+rowsB+3;
							data[1] = i;
							data[2] = j;
							for(int k=0;k<2*colsA;k+=2){
								data[k+3] = *(matA+i*colsA+(k/2));
								data[k+4] = *(matB+(k/2)*colsB+j);
								//printf("%d,%d\n",*(matA+i*colsA+(k/2)),*(matB+(k/2)*colsB+j));
							}
							pthread_create ((thread+i*colsB+j), NULL, multiplyMatrix,data);
							sleep(0);
						}
					}
					printf("\nThreads Created\n");
					for(int i=0;i<rowsA;i++){
						for(int j=0;j<colsB;j++){
							void *k;
							pthread_join (*(thread+i*colsB+j), &k) ;
							int *p=(int *)k;
							*(resMat + i*colsB +j) = *p;
							free(p);
	  						
						}
					}
					printf("\nResultant Matrix: \n");
					displayMatrix(resMat,rowsA,colsB);
				}
				else{
					printf("\nNumber of Columbns of Matrix A not equal to Number of rows of Matrix B\n");
				}
				
			break;
			
			case 4:
				x=0;
			break;
			
			default:
				printf("\nInvalid Choice\n");
		}	
	}
	
	
	
	
	
	
	
	return 0;
}
