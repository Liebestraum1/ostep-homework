#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void printLog(char* member, char* message){
    printf("[%6s][PID:%d] %-25s \n", member, getpid(), message);
}

int main(){
    int fd;
    fd = open("./text.txt", O_RDWR | O_CREAT, 0644);
    int rc = fork();

    if (rc < 0) {  
	fprintf(stderr, "[%6s] fork failed\n", "ERROR");
	exit(1);
    } else if(rc == 0) {
	for(int i = 0; i < 5; i++){
	    sleep(1);
	    write(fd, "C", 1);
	    printLog("CHILD", "write 'C' to file descriptor");
	}
	printLog("CHILD", "process complete");
    } else {
	for(int i = 0; i < 5; i++){
	    sleep(1);
	    char buf;
	    read(fd, &buf, 1);

	    printf("PARENT READ FROM FILE DESCRIPTOR: %c\n", buf);
	    sleep(1);

	    write(fd, "P", 1);
	    printLog("PARENT", "write 'P' to file descriptor");
	}
	printLog("PARENT", "process complete");
    }
    return 0;
}
