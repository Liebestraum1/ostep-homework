#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void printLog(char* member, char* message, int var, int* varAddress){
	printf("[%6s][PID:%d] %-25s| variable x: %d | address of x: %p\n", member, getpid(), message, var, varAddress);
}



int main(){
    int x = 100;
    int rc = fork();

    if(rc < 0) {
	fprintf(stderr, "[ ERROR] fork failed\n");
	exit(1);
    } else if(rc == 0){
	printLog("CHILD", "before change", x, &x);
	x = 200;
	printLog("CHILD", "after change", x, &x);
    } else {
	wait(NULL);
	printLog("PARENT", "child process complete", x, &x);
	printLog("PARENT", "parent process", x, &x);
    }
    return 0;    
}
