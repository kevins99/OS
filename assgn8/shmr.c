#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct {
	char datawrite[30];
}buffer;

int main(void) {
	key_t key = 6000;
	int shmid = shmget(key, sizeof(buffer), 0666 );
	if (shmid == -1) {
		printf("reader create error");
		return 0;
	}

	char *shm = (char*)shmat(shmid, NULL, 0);
	if (shm == '-1'){
		printf("reader attach problem");
		return 0;
	}	
	printf("Reader program\n");
	char *s = shm;
	int count = 0;
	for(s=shm; *s!='$'; s++) {
		if( *s != '$') {
			char c = *s;
			putchar(c);
			count++;	
		}
	}
	putchar('\n');
		//printf("%s\n", buff);
		//printf("%c", s);
}
