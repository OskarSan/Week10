#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <fcntl.h>
#include <string.h>



int main(int argc, char *argv[]) {
  

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {

        if (strcmp(argv[1], "-") != 0){
            int file = open(argv[1], O_RDONLY);
            if (file < 0){
                perror("open");
                exit(1);
            }

            dup2(file, 0);
        }
        if (strcmp(argv[2], "-") != 0){
            FILE *f = fopen(argv[2], "w");
            if (f == NULL){
                perror("fopen");
                exit(1);
            }
            dup2(fileno(f), fileno(stdout));
            fclose(f);
        }

        execvp(argv[3], &argv[3]);
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