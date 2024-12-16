#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 



int main(int argc, char *argv[]) {
  

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(1);
    } else {
        printf("Child process %d created\n", pid);
        int status;
        waitpid(pid, &status, 0);
        printf("Child process %d exited with status %d\n", pid, status);
    }


    return 0;
}