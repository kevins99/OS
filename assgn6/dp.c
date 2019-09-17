#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t s[5];


void* diningp(void *arg) {
	int i = *(int*)arg;
	printf("Philosopher %d wants to eat\n", i);
	while(i) {
		if((i)%2 == 0) {
			sem_wait(&s[i]);
			sem_wait(&s[(i+1)%5]);
		}
		else {
			sem_wait(&s[(i+1)%5]);
			sem_wait(&s[i]);
		}
		
		printf("Philo %d is eating\n", i);
		sleep(rand()%10);
		
		
		
		sem_post(&s[i]);
		sem_post(&s[(i+1)%5]);
		
		
		printf("Philo %d done eating\n", i);
//		sleep(rand()%2);
		/*else {
			sem_post(&s[(i+1)%5]);
			sem_post(&s[i]);
		}*/
		
	}
}

void init() {
	int i;
	for (i=0; i<5; i++) {
		sem_init(&s[i], 0, 1);
	}
	
}
int main() {
	int i;
	pthread_t p[5];
	init();
	printf("creating threads\n");
	for(i=0; i<5; i++) {
		int* arg = (int*)malloc(sizeof(int));
		*arg = i;
		pthread_create(&p[i], NULL, *diningp, (void *)arg);
		sleep(1);
	}
	
	for(i=0; i<5; i++) {
		pthread_join(p[i], NULL);
	}
	
}
