#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	char datawrite[30];
}buffer;

int main(void) {
	int in, i;
	key_t key = 6000;
	int shmid = shmget(key, sizeof(buffer), IPC_CREAT | 0666);
	if (shmid<0) {
		printf("Writer create error");
		return 0;
	}
	char *shm = (char *)shmat(shmid, NULL, 0);
	if (shm < 0){
		printf("Error in attaching");
		return 0;
	}
	
	char str[100];
	scanf("%s", str);
	char *s = shm;
	printf("WRITING: ");
	for(i=0; i< strlen(str); i++) {
		char c = str[i];
		putchar(c);
		*s++ = c;
	}

	(*(s++)) = '$';
	printf("\n");

	//printf("\nWRITER SLEEPING\n");
	while (*shm!= '*')
		sleep(1);
	//return 0;
}
