#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int pipe1[2], pipe2[2], pipe3[2];
    pid_t pid, child_pid;

    // pipe error handling
    if (pipe(pipe1) == -1) {
        perror("Error: creating pipe1.\n");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe2) == -1) {
        perror("Error: creating pipe2.\n");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe3) == -1) {
        perror("Error: creating pipe2.\n");
        exit(EXIT_FAILURE);
    }

    // create child process
    pid = fork();

    if (pid == -1) {
        perror("Error: system call fork() failed.\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // child process
        //unused pipe
        close(pipe3[0]);
        close(pipe3[1]);
        close(pipe1[1]);
        close(pipe2[0]);

        int num;

        while(1){
            // Read from pipe1
            if (read(pipe1[0], &num, sizeof(num)) != sizeof(num)) {
                perror("Error: reading from pipe 1.\n");
                exit(EXIT_FAILURE);
            }

            if(num == -1){
                if (write(pipe2[1], &num, sizeof(num)) != sizeof(num)) {
                    perror("Error: writing to pipe 2.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            }

            num *= num;

            if (write(pipe2[1], &num, sizeof(num)) != sizeof(num)) {
                perror("Error: writing to pipe 2.\n");
                exit(EXIT_FAILURE);
            }
        }
        exit(EXIT_SUCCESS);

    } else { // parent process
        child_pid = fork();

        if (child_pid == -1) { // error handling
            perror("Error: system call fork() failed.\n");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) { // child 2
            //close unused pipes ends
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[1]);
            close(pipe3[0]);

            int num;

            // read from pipe 2
            while(1){
                if (read(pipe2[0], &num, sizeof(num)) != sizeof(num)) {
                    perror("Error: reading from pipe 2.\n");
                    exit(EXIT_FAILURE);
                }

                if(num == -1){
                    break;
                }

                // perform calculation
                num = num + 1;

                // write to pipe 3
                if (write(pipe3[1], &num, sizeof(num)) != sizeof(num)) {
                    perror("Error: writing to pipe 3.\n");
                    exit(EXIT_FAILURE);
                }
            }
            exit(EXIT_SUCCESS);
            
        } else { // parent
            // close unused pipe
            close(pipe2[0]);
            close(pipe2[1]);
            close(pipe1[0]);
            close(pipe3[1]);
            
            int status;
            
            int num;
            printf("Enter an integer (EOF or -1 to exit): ");
            while (scanf("%d", &num) != EOF) {
                if(num == -1){
                    break;
                }
                if (write(pipe1[1], &num, sizeof(num)) != sizeof(num)) {
                    perror("Error: writing to pipe 1.\n");
                    exit(EXIT_FAILURE);
                }
                if(num != -1){
                    if (read(pipe3[0], &num, sizeof(num)) != sizeof(num)) {
                        perror("Error: reading from pipe 3.\n");
                        exit(EXIT_FAILURE);
                    }

                    printf("Result: %d\n", num);
                    printf("Enter an integer (EOF or -1 to exit): ");
                }
            }

            // Send termination signal
            if(num != -1){
                num = -1;
                printf("\n");
            }
            write(pipe1[1], &num, sizeof(num));

            close(pipe1[1]);
            close(pipe3[0]);

            waitpid(pid, &status, 0);
            waitpid(child_pid, &status, 0);

            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}