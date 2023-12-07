#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(void){
    int pipe1[2], pipe2[2];
    pid_t pid, pid2;

    if(pipe(pipe1) == -1){
        perror("Error: creating pipe.\n");
        exit(EXIT_FAILURE);
    }

    if(pipe(pipe2) == -1){
        perror("Error: creating pipe.\n");
        exit(EXIT_FAILURE);
    }

    // first child -- square function
    pid = fork();
    if(pid == -1){ // error handling
        perror("Error: system call fork() failed.\n");
        exit(EXIT_FAILURE);
    } else if(pid == 0){ // child process
        close(pipe1[1]); // close write end of first pipe
        close(pipe2[0]); // close read end of second pipe

        int num;
        if(read(pipe1[0], &num, sizeof(num)) != sizeof(num)){
            perror("Error: reading number from pipe.\n");
            exit(EXIT_FAILURE);
        }

        num *= num;

        if(write(pipe2[1], &num, sizeof(num)) != sizeof(num)){
            perror("Error: writing number to pipe.");
            exit(EXIT_FAILURE);
        }

        close(pipe1[0]);
        close(pipe2[1]);

        exit(EXIT_SUCCESS);
    } else { // parent process
        pid2 = fork();

        if(pid2 == -1){
            perror("Error: system call fork() failed.\n");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0){
            close(pipe1[0]); // close read end of pipe1
            close(pipe2[1]); // close write end of pipe2



        } else {
            wait(pid, NULL, 0);
            wait(pid2, NULL, 0);

        }

    }


    return 0;
}