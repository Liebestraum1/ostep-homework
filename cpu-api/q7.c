#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork failed");
	} else if (rc == 0){
		close(STDOUT_FILENO);
		printf("CHILD PROCESS: %d\n", getpid());
	} else {
		printf("PARENT PROCESS: %d\n", getpid());
	}
}
