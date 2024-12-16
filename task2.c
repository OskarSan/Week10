#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

int main(int argc, char *argv[]) {
     
    char command[256] = {0};
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    printf("system():\n");
    system(command);


    printf("\nexecvp():\n");
    execvp(argv[1], &argv[1]);

    printf("process doesnt continue");

    return 0;
}