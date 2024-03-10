#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
	close(fd[0]);
	
	
	sleep(1);	
	write(fd[1], "data", 4);
	printf("Child PID: %d\n", getpid());
    	//sleep(100);
    }
    else
    {
        printf("Parent PID: %d\n", getpid());
	char buffer[5];
	
	close(fd[1]);
	
	
	read(fd[0], buffer, 4);
	buffer[4] = 0;
	printf("[%s]", buffer);
    }
    wait(NULL);
    return 0;
}
