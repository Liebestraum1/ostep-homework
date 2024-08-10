#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int fd[2];

	if(pipe(fd) < 0){	// making pipe for children processes
		fprintf(stderr, "fork failed");
		exit(1);
	}

	int rc = fork(); // create first child process

	if(rc < 0){
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0){
		close(fd[0]); // close fd of pipe which is in charge of reading
		printf("first child process pid: %d\n", getpid());

		dup2(fd[1], 1);	// remap stdout to fd of pipe which is in charge of writing 
		printf("HELLO I'M FIRST CHILD PROCESS [%d]", getpid()); // it will print to fd[1];
		close(fd[1]);
	} else {
		int rd = fork(); //create second child process	

		if(rd < 0){
			fprintf(stderr, "fork failed");
			exit(1);
		} else if (rd == 0){
			close(fd[1]); // close fd of pipe which is in charge of writing
			printf("second child process pid: %d\n", getpid());
			
			dup2(fd[0], 0); // remap stdin to fd of pipe which is in charge of reading
			
			char buf[255];
			scanf("%[^\n]s", buf); // read from stdin which is remmaped by dup2 from terminal to pipe (reading) 

			printf("second child read from first child: %s, second child pid: %d\n", buf, getpid());
			close(fd[0]);
		} else {
			close(fd[0]);
			close(fd[1]);
		}
	}
	return 0;
}
