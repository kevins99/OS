// Kevin Stephen
// 33165
// Single producer consumer

#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

sem_t full, empty, mutex;
int i=-1, *buffer, size;

void *producer (void *x1) {
	printf ("\n-- producer --\n");
	while(1) {
		sem_wait (&empty);
		sem_wait (&mutex);
			
		srand(0);
		i++;
		buffer[i] = rand()%(size*size);
		printf ("\nproduced : %d\tat location : %d\n", buffer[i], i);
		sleep (1);
		
		sem_post (&mutex);
		sem_post (&full);
	}
}

void *consumer (void *x1) {
	printf("\n-- consumer --\n");
	while(1) {
		sem_wait (&full);
		sem_wait (&mutex);
		
		printf ("\nconsumed : %d\tat location : %d\n", buffer[i], i);
		i--;
		sleep(1);
		
		sem_post (&mutex);
		sem_post (&empty);
	}
}
 
int main() {
	printf ("Enter size of buffer : ");
	scanf ("%d", &size);
	
	sem_init (&mutex, 0, 1);
	sem_init (&full, 0, 0);
	sem_init (&empty,0, size);
	pthread_t t1, t2;
	buffer = (int *) malloc (size*sizeof(int));
	pthread_create (&t1, NULL, consumer, NULL);
	sleep(1);
	pthread_create (&t2, NULL, producer, NULL);
	
	pthread_join (t1,NULL);
	pthread_join (t2,NULL);
	
	return 0;
}
