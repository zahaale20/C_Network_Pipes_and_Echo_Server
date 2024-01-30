# C_Network_Pipes_and_Echo_Server

## Description:
The "C_Network_Pipes_and_Echo_Server" GitHub repository contains two distinct C programming tasks demonstrating advanced concepts in inter-process communication and network programming. The project is a deep dive into the practical application of pipes and socket programming in C.

### Task 1 - Square Plus One Using Pipes:
Program Name: square_plus1.
Functionality: This program reads integers from the keyboard until EOF. It creates two child processes, forming a ring structure with pipes.
Process Communication:
The parent process sends an integer to the first child.
The first child squares the number and passes it to the second child.
The second child adds one to the number and sends it back to the parent.
The parent prints the final value and continues this cycle until EOF.
Resource Management: On EOF, the parent closes its pipes and waits for the children to exit properly, ensuring clean termination and resource handling.

### Task 2 - Echo Server:
Starter Code Modification: The provided base code for a simple server and client is modified for echo functionality.
Server-Client Interaction:
The client sends data to the server.
The server echoes the data back to the client.
The client receives and prints the echoed data.
Port Configuration: A unique port number between 1024 and 65535 is used for communication, allowing testing on university servers or locally.
Networked Program Foundation: This task provides a fundamental understanding of building networked applications and testing connection setups.

## Repository Contents:
- Source code for the square_plus1 pipe communication program.
- Modified server and client code for the echo server task.
- Documentation detailing each program's functionality, usage, and implementation.
- Additional resources and notes on network programming and process communication in C.

To compile task1:
    'make'

    NOTE: make sure you cd in the right directory

To run task1:
    1. In terminal type './ squareplus1'
    2. Input valid integers
    3. Control + d or input -1 to terminate


To compile task2:
    'make'

    NOTE: make sure you cd in the right directory

To run task2: 
    1. split terminal
    2. Input './server' on one terminal
    3. Input './client localhost' on the other terminal
    4. In the client terminal, input a value
    5. Use control + c to terminate. Must be done in each terminal
