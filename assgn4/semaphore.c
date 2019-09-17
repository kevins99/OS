//Kevin Stephen
//33165
//Multiple producer and consumer
#include <pthread.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>



#define SIZE 10 //of buffer
#define NUM 20

typedef struct queue
{
	int arr[SIZE];
	int in;
	int out;
	sem_t full;
	sem_t empty;
	pthread_mutex_t lock;
}queue;

queue buffer;
int item=1;


void* producer(void* arg)
{
	int index,z;
	index=*(int*)arg;
	int value;
	
	while(1)
	{
		z=(rand()%10)+1;
		sleep(z);
		sem_wait(&buffer.empty);
		sem_getvalue(&buffer.empty,&value);
		if(value==0)
			printf("\n\nBuffer is full.\n\nProducer waiting to produce item\n\n");
			
		pthread_mutex_lock(&buffer.lock);
		printf("\n\nProducer %d is producing item %d",index,item);
		buffer.arr[(buffer.in++)%SIZE]=item++;
		pthread_mutex_unlock(&buffer.lock);
		sem_post(&buffer.full);		
	}	
		
	
	
}

void* consumer(void* arg)
{
	int index;
	int cons;
	index=*(int*)arg;
	int value,z;
	
	//printf("\n\nConsumer %d starts consuming\n\n",index);
	while(1)
	{
		z=(rand()%10)+4;
		sleep(z);
		sem_wait(&buffer.full);
		sem_getvalue(&buffer.full,&value);
		if(value==SIZE)
			printf("\n\nBuffer is empty.\n\nConsumer waiting to consume item\n\n");
			
	      pthread_mutex_lock(&buffer.lock);
		cons=buffer.arr[(buffer.out++)%SIZE];	
		
		printf("\n\nConsumer %d is consuming item %d",index,cons);
		pthread_mutex_unlock(&buffer.lock);
		sem_post(&buffer.empty);		
	}	
}


void init()
{
	buffer.in=0;
	buffer.out=0;
	sem_init(&buffer.full, 0, 0);  //int sem_init(sem_t *sem, int pshared, unsigned int value);
	//pshared=0,semaphore is shared between resources. value=initial value of semaphore
	sem_init(&buffer.empty,0,SIZE);
	
}	


void main()
{
	int i;
	pthread_t consumer_t[SIZE],prod_t[SIZE];
	//sem_wait blocks access to the semaphore.
	int nprod,ncons; //number of producers and consumers.
	init();
	
	printf("\n\nEnter number of producers::");
	scanf("%d",&nprod);
	
	printf("\n\nEnter number of consumers::");
	scanf("%d",&ncons);
	
	for (i = 0; i < nprod; i++) 
	{
     		 pthread_create(&prod_t[i], NULL,*producer, &i);
     		 printf("\n\nProducer %d starting\n\n",i);
    	}
    	
    	for (i = 0; i < ncons; i++) 
	{
     		pthread_create(&consumer_t[i], NULL,*consumer, &i);
     		 printf("\n\Consumer %d starting\n\n",i);
    	}
    	for (i = 0; i < nprod; i++) 
	{
     		 pthread_join(prod_t[i], NULL);
    	}
	
	for (i = 0; i < ncons; i++) 
	{
     		 pthread_join(&consumer_t[i], NULL);
    	}
	


}
