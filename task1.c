#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[]) {
    
    int fd = open(argv[1], O_RDWR);
        if(fd == -1) {
                printf("Unable to open the file\n");
                exit(1);
        }

    time_t t;
    int pid = getpid();

    time(&t);
        printf("pid: %3d, getting exclusive lock at %s\n", pid, ctime(&t));
        flock(fd, LOCK_EX);
        time(&t);
        printf("pid: %4d, exclusive locked at %s\n", pid, ctime(&t));
        sleep(20);
    

    flock(fd, LOCK_UN);
        time(&t);
        printf("pid: %4d, unlocked at %s\n", pid, ctime(&t));   


    flock(fd, LOCK_SH);
        time(&t);
        printf("pid: %4d, shared locked at %s\n", pid, ctime(&t));
        sleep(10);

    
    flock(fd, LOCK_UN);
        time(&t);
        printf("pid: %4d, unlocked at %s\n", pid, ctime(&t));   

    close(fd);

    return 0;
}