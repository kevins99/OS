#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void)
{
char write_msg[BUFFER_SIZE]="HELLO";
char read_msg[BUFFER_SIZE]="Tatti";
int fd[2];
pid_t pid;
/* create the pipe */
if (pipe(fd) == -1) {
fprintf(stderr,"Pipe failed");
return 1;
}
// fork a child process
pid = fork();
if (pid < 0) { //I* error occurred *I
fprintf(stderr, "Fork Failed");
return 1;
}
if (pid > 0) {// I* parent process *I
//I* close the unused end of the pipe
close(fd[READ_END]);
//*I
//I* write to the pipe *I
write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
//I*
//close the write end of the pipe
close(fd[WRITE_END]);
//*I
}
else { //I* child process *I
//I* close the unused end of the pipe
close(fd[WRITE_END]);
//*I
//I* read from the pipe *I
read(fd[READ_END], read_msg, BUFFER_SIZE);
printf ("%s\n", read_msg) ;
//I*
//close the write end of the pipe
close(fd[READ_END]);
//*I
}
return 0;
}
