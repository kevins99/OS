#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>  
#include <stdlib.h>   
	
int main() {
	int file, choice = 1;
	size_t n;
	char filename[20], *bufferwrite, *bufferread;//, O_RDONLY, O_CREATE, O_APPEND, O_WRONLY;
	
	printf("Enter file name : ");
	scanf("%s", filename);
	
	while(choice > 0 && choice < 4) {
		printf("\nSelect operation : \n1. Create file\n2. Write to file\n3. Read from file\n4.Exit\n");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				file = open(filename, O_CREAT);
				close(file);
				break;
			
			case 2:
				file = open(filename, O_CREAT | O_WRONLY);
				printf("Enter data to write to file : ");
				getline(&bufferwrite, &n, stdin);//scanf("%s", buffer);
				write(file, (char *)bufferwrite, strlen(bufferwrite));
				close(file);
				break;
				
			default:
				choice = -1;
		}	
	}
	
	return 0;
}
