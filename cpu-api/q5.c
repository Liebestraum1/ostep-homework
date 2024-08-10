#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int rc = fork();

	if(rc < 0){
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0){
		int w = wait(NULL);
		printf("child process id: %d, wait: %d\n", getpid(), w);
	} else {
		int w = wait(NULL);
		printf("parent process wait: %d\n", w);
	}
	return 0;
}
