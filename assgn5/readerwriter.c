#include <pthread.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
//#include <file.h>

#define SIZE 10
int position=0; //nth character to be read.
sem_t wsem;
sem_t rsem;
pthread_mutex_t lock;
int read_count;



void* writer(void* arg)
{
	//resource 'antony' always unlocked.
	
	int index,z;
	
	char buffer[7];
	index=*(int*)arg; //nth writer.
	int value;
	FILE *mainfp,*writerfp; //mainfp for 'antony', writerfp for 'filewrite'
	mainfp=fopen("antony","r");//IN READ MODE 
	if(mainfp!=NULL)
	{
		writerfp=fopen("filewrite","a"); //append mode
		if(writerfp!=NULL)
		{
			while(1)
			{
				z=(rand()%10)+index;
						
				//sem_wait(&wsem);
			
				pthread_mutex_lock(&lock);
				
				printf("\n\nWriting %d into file %d",z,index);
				//CRITICAL SECTION START
				/*fread(&buffer,6*sizeof(char), 1, mainfp);
				printf("\nreading file");	
				printf("\n\nWriter %d is writing %s \n\n",index,buffer);
				fwrite(&buffer,sizeof(buffer),1,writerfp);
				
				fseek(mainfp,6,SEEK_CUR);*/	
				//CRITICAL SECTION END
				pthread_mutex_unlock(&lock);
				//sem_post(&rsem);
			}
			fclose(mainfp);
			fclose(writerfp);
		}	
		
	}
}

void* reader(void* arg)
{
	int reader_count=0;
	FILE *writerfp,*mainfp ;
	writerfp=fopen("filewrite","r");
	
	int index,z;
	
	char buffer[7];
	index=*(int*)arg; //nth reader.
	int value;
	if(writerfp!=NULL)
	{
		printf("\Reader %d is reading\n\n",index);
		while(1)
		{
			z=(rand()%10)+1;
			
			pthread_mutex_lock(&lock);
			read_count++;
			
			if(read_count==1) //block writer
				sem_wait(&wsem);
			
			pthread_mutex_unlock(&lock);
			
			/*fread(buffer, 1, 6, writerfp);
			printf("\n\nReader %d is reading %s\n\n",index,buffer);
			fseek(writerfp,6,SEEK_CUR);
			*/
			pthread_mutex_lock(&lock);
			
			read_count--;
			if(read_count==0)
				sem_wait(&wsem);
				
			pthread_mutex_unlock(&lock);
			sleep(z);	
		}
			fclose(writerfp);
		}
}


void init()
{
    pthread_mutex_init(&lock,NULL);
    sem_init(&wsem, 0, 0); 
    sem_init(&rsem, 0, 0); 
    read_count=0;
}

void main()
{
	int i;
	pthread_t read_t[SIZE],write_t[SIZE];
	//sem_wait blocks access to the semaphore.
	int nprod,ncons; //number of producers and consumers.
	init();
	
	printf("\n\nEnter number of writers::");
	scanf("%d",&nprod);
	
	printf("\n\nEnter number of readers::");
	scanf("%d",&ncons);
	
	
	init();
	for (i = 0; i < nprod; i++) 
	{
     		 pthread_create(&write_t[i], NULL,*writer, &i);
     		 printf("\n\nWriters %d starting\n\n",i);
    	}
    	
    	for (i = 0; i < ncons; i++) 
	{
     		pthread_create(&read_t[i], NULL,*reader, &i);
     		 printf("\n\nReaders %d starting\n\n",i);
    	}
    	for (i = 0; i < nprod; i++) 
	{
     		 pthread_join(write_t[i], NULL);
    	}
	
	for (i = 0; i < ncons; i++) 
	{
     		 pthread_join(&read_t[i], NULL);
	}

}
/*

refer to :: https://stackoverflow.com/questions/51342595/is-readers-writers-just-producer-consumer-with-multiple-consumers




Producer: produces a message. Also, he has to read the queue pointers to determine where to write the next item and to determine if the buffer is full.

Consumer: The consumer is not just a reader, because it must adjust the queue pointers to show that it has removed a unit from the buffer.

Writer: Writers are processes which exclude all the others when writing a file, readers and writers alike.

Reader: Readers are processes which are not required to exclude one another. Any number of readers may simultaneously read the file.

Reference : "Operating Systems" William Stallings
*/
