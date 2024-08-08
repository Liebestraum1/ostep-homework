#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void printLog(char* member, char* message){
    printf("[%6s][PID:%d] %-25s \n", member, getpid(), message);
}

int main(){
	int rc = fork();

	if (rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		printLog("CHILD", "hello!");
	} else {
		wait(NULL);
		printLog("PARENT", "goodbye.");
	}
	return 0;
}
