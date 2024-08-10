#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void printLog(char* member, char* message){
    printf("[%6s][PID:%d] %-25s \n", member, getpid(), message);
}

int main(){
	int fd[2];

	if(pipe(fd) < 0){
		fprintf(stderr, "pipe failed");
		exit(1);
	};

	int rc = fork();

	if (rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		close(fd[0]);

		printLog("CHILD", "hello!");
		write(fd[1], "1", 1);

		close(fd[1]);
	} else {
		close(fd[1]);
		char c;
		sleep(10);
		read(fd[0], &c, 1);
		printLog("PARENT", "goodbye.");

		close(fd[0]);
	}
	return 0;
}
