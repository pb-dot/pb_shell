#include "header.h"
//args is array of string where each string is input token get from parsing
// args = echo "hello" < rm.txt ==> args[0] = echo args[1] = hello args[2] = < args[3] = rm.txt 
//args[4]= null

int contains_chain(char **args) {
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "&&") == 0 || strcmp(args[i], "||") == 0 || strcmp(args[i], ";") == 0 ) {
            return 1;
        }
        i++;
    }
    return 0;
}

void handle_chain(char ** args) {
    char **args1 = args;
    char **args2 = NULL;
    pid_t pid;
    int flag; // 1 for ; 2 for && 3 for ||
    int status;

    while (*args != NULL) {
        if (strcmp(*args, ";") == 0) {
            *args = NULL; // setting current token (;) to NULL
            args++;
            args2 = args;
            flag =1;
            break;
        }
        else if (strcmp(*args, "&&") == 0) {
            *args = NULL; // setting current token (;) to NULL
            args++;
            args2 = args;
            flag =2;
            break;
        }
        else if (strcmp(*args, "||") == 0) {
            *args = NULL; // setting current token (;) to NULL
            args++;
            args2 = args;
            flag =3;
            break;
        }
        args++;// move on to next input token
    }
	
	// The above while loop ensures args1 has left half of || (or) and args2 has right half

	    pid = fork();
	    if (pid == -1) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	    }
	    else if (pid == 0) { // Child process
		if (execvp(args1[0], args1) == -1) {// executing the left half of ;
		    perror("execvp failed");
		    exit(EXIT_FAILURE);
		}
	    }
	    else { // Parent process
		wait(&status); // Wait for child process to finish
		if(flag == 1){
			if (execvp(args2[0], args2) == -1) {// executing the second half of |
			    perror("execvp failed");
			    exit(EXIT_FAILURE);
			}
		}
		else if(flag ==2 && status == EXIT_SUCCESS){
			if (execvp(args2[0], args2) == -1) {// executing the second half of |
			    perror("execvp failed");
			    exit(EXIT_FAILURE);
			}
		}
		else if(flag == 3){
			if (execvp(args2[0], args2) == -1) {// executing the second half of |
			    perror("execvp failed");
			    exit(EXIT_FAILURE);
			}
		}
	    }
	
}
