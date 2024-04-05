#include "header.h"
//args is array of string where each string is input token get from parsing
// args = echo "hello" < rm.txt ==> args[0] = echo args[1] = hello args[2] = < args[3] = rm.txt 
//args[4]= null

void execute_command(char **args) {
    if (args[0] == NULL) {
        return;
    }

    if (strcmp(args[0], "cd") == 0) {
        if (shell_cd(args) != 0) { // cd is internal command for bash
            fprintf(stderr, "cd: error\n");
        }
    }
    else if (strcmp(args[0], "exit") == 0) { // exit is internal command
    	printf("Bye Bye ...\n\n");
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(args[0], "clear") == 0) { // clear is internal command
        system("clear");
    }
    else if (strcmp(args[0], "hist") == 0) { // history 
    	exe_prev_cmd();
    }
    else {    
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork failed");
            }
            else if (pid == 0) { // Child Process
		        if (contains_redirect(args)) {// cmd has  > <
            			handle_redirect(args);
        		}
        		else if (contains_pipe(args)) {// cmd has |
        			pipe_commands(args);
        		}
        		else if(contains_chain(args)){// cmd has && || ;
        			handle_chain(args);
        		}
        		else{// normal cmd
        		      if (execvp(args[0], args) == -1) {
                    			perror("execvp");
                    			exit(EXIT_FAILURE);
                	      }
        		}
        		
            }
            else {// Parent Process
                wait(NULL);
            }    
    }
}

int shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
    return 0;
}

