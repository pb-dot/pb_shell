#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>

#define MAX_COMMAND_LENGTH 1024
#define BUFFER_SIZE 1024
#define HISTORY_SIZE 3
#define TOKEN_DELIMITER " \t\r\n\a"

extern char **history;
extern int history_index , h_ptr ,history_size;


// Function declarations
void execute_commands_from_file(const char *filename);
char **parse_line(char *line);
void execute_command(char **args);
int shell_cd(char **args);// for cd
int contains_redirect(char **args);
void handle_redirect(char **args);
int contains_pipe(char **args);
void pipe_commands(char **args);
char *replace_env_var(char *);

void add_to_history(char *line);
char *get_previous_command();
char *get_next_command();
void exe_prev_cmd();

int contains_chain(char ** args);
void handle_chain(char ** args);


#endif
