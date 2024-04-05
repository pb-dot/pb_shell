#include "header.h"
//args is array of string where each string is input token get from parsing
// args = echo "hello" < rm.txt ==> args[0] = echo args[1] = hello args[2] = < args[3] = rm.txt 
//args[4]= null

int contains_redirect(char **args) {
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0 || strcmp(args[i], ">>") == 0 ) {
            return 1;
        }
        i++;
    }
    return 0;
}

void handle_redirect(char **args) {// args[i] has  token


    int i = 0;
    int in_fd, out_fd;
    char *input_file, *output_file;
    while (args[i] != NULL) {
        if (strcmp(args[i], "<") == 0) {
            input_file = args[i + 1];
            in_fd = open(input_file, O_RDONLY);// open in read mode
            if (in_fd < 0) {
                perror("open sys call failed");
                exit(EXIT_FAILURE);
            }
            dup2(in_fd, STDIN_FILENO);// redirect stdin to in_fd
            close(in_fd);
            args[i] = NULL;// setting current token ie > to null
            break;
        }
        else if (strcmp(args[i], ">") == 0) {
            output_file = args[i + 1];
            out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0664);//open in write mode
            if (out_fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(out_fd, STDOUT_FILENO);// redirect stdout to out_fd
            close(out_fd);
            args[i] = NULL;// setting current token ie > to null
            break;
        }
        else if (strcmp(args[i], ">>") == 0) {
            output_file = args[i + 1];
            out_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0664);// open in append mode
            if (out_fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
            args[i] = NULL;
            break;
        }
        i++;
    }
	
	// executing the left hand side of > or < or >>
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }

}

