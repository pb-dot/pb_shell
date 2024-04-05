#include "header.h"

//args is array of string where each string is input token get from parsing
// args = echo "hello" < rm.txt ==> args[0] = echo args[1] = hello args[2] = < args[3] = rm.txt 
//args[4]= null

int contains_pipe(char **args) { // checks if the input has | or not
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "|") == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

void pipe_commands(char **args) {
    int pipefd[2];
    pid_t pid;
    char **args1 = args;
    char **args2 = NULL;

    while (*args != NULL) {
        if (strcmp(*args, "|") == 0) {
            *args = NULL; // setting current token (|) to NULL
            args++;
            args2 = args;
            break;
        }
        args++;// move on to next input token
    }
	
	// The above while loop ensures args1 has left half of | (pipe) and args2 has right half	
	
    if (pipe(pipefd) == -1) {
        perror("pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // Child process
        close(pipefd[0]); // Close the unused read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
        close(pipefd[1]); // Close the write end of the pipe
        if (execvp(args1[0], args1) == -1) {// executing the left half of |
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    }
    else { // Parent process
        wait(NULL); // Wait for child process to finish
        close(pipefd[1]); // Close the write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
        close(pipefd[0]); // Close the read end of the pipe
        if (execvp(args2[0], args2) == -1) {// executing the second half of |
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
}

