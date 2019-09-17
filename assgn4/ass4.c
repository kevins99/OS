#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>

typedef struct queue {
	sem_t full;
	sem_t empty;
	sem_t mutex;
	int in;
	int out;
}

int i = -1;
queue buffer;


