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
        if(read(pipe1[0], &num, sizeof(num)) != sizeof(int)){
            perror("Error: reading number from pipe.\n");
            exit(EXIT_FAILURE);
        }

        num *= num;

        if(write(pipe2[1], &num, sizeof(num)) != sizeof(int)){
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

            int num;

            if(read(pipe2[0], &num, sizeof(num)) != sizeof(int)){
                perror("Error: reading number from pipe.\n");
                exit(EXIT_FAILURE);
            }

            num += 1;

            if(write(pipe1[1], &num, sizeof((num)) != sizeof(int))){
                perror("Error: writing number to pipe.\n");
                exit(EXIT_FAILURE);
            }

            close(pipe1[1]);
            close(pipe2[0]);

            exit(EXIT_SUCCESS);

        } else {
            close(pipe1[1]);
            close(pipe2[0]);

            int num;
            while(scanf(%d, &num) != EOF){
                if(write(pipe1[1], &num, sizeof(num)) != sizeof(int)){
                    perror("Error: writing number to child process.\n");
                    exit(EXIT_FAILURE);
                }
                if(read(pipe2[0], &num, sizeof(num)) != sizeof(int)){
                    perror("Error: reading number from child process.\n");
                    exit(EXIT_FAILURE);
                }
                
                printf("Result: %d\n", num);
                printf("Enter an integer (EOF to exit): ");
            }

            close(pipe1[1]);
            close(pipe2[0]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

        }

    }


    return 0;
}