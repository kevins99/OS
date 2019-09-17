#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int readcnt;
sem_t wrt,mutex;        

int globalData;


void *reader(void *d){
	int *data;
	data = (int *)d;
	int no = *data;
	printf("\nReader %d Started",no);
	
	while(1){
		printf("\n\nReader %d waiting to read",no);
		sem_wait(&mutex);
		
		readcnt++;
		if(readcnt==1){
			sem_wait(&wrt);
		}
		
		sleep(rand()%3);
		sem_post(&mutex);
		
		printf("\n\nReader %d reads %d",no,globalData);
		printf("\nRead Count: %d",readcnt);
		
		sem_wait(&mutex);
		
		readcnt--;
		if(readcnt==0){
			sem_post(&wrt);
		}
		sleep(rand()%5);
		sem_post(&mutex);
	}
	
	pthread_exit(NULL);
}

void *writer(void *d){
	int *data;
	data = (int *)d;
	int no = *data;
	printf("\nWriter %d Started",no);
	
	while(1){
		printf("\n\nWriter %d waiting to write",no);
		sem_wait(&wrt);
		
		globalData = rand()%10;
		printf("\n\nWriter %d wrote %d",no,globalData);
		printf("\nValue of Global Data: %d",globalData);
		printf("\nRead Count: %d",readcnt);
		sleep(rand()%5);
		
		sem_post(&wrt);
	}
	
	pthread_exit(NULL);
}                                         

int main(){
	int res;
	pthread_t threadReader[4],threadWriter[4];
	int no;
	
	res = sem_init(&wrt, 0, 1);
	if (res != 0) {
		perror("\nWrite Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	res = sem_init(&mutex, 0, 1);
	if (res != 0) {
		perror("\nMutex Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	
	for(int i=0;i<4;i++){
		no=i;
		res = pthread_create(&threadReader[i], NULL, reader, &no);
		sleep(1);
		if (res != 0) {
			perror("\nReader Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	
	
	for(int i=0;i<4;i++){
		no=i;
		res = pthread_create(&threadWriter[i], NULL, writer, &no);
		sleep(1);
		if (res != 0) {
			perror("\nWriter Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	
	
	printf("\nWaiting for thread to finish...\n");
	for(int i=0;i<4;i++){
		res = pthread_join(threadReader[i], NULL);
		if (res != 0) {
			perror("\nReader Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	
	for(int i=0;i<4;i++){
		res = pthread_join(threadWriter[i], NULL);
		if (res != 0) {
			perror("\nWriter Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	
	printf("\nThread joined\n");
	sem_destroy(&wrt);
	sem_destroy(&mutex);
	
	exit(EXIT_SUCCESS);
}


