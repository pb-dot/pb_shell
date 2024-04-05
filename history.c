#include "header.h"

char **history = NULL;
int history_size = HISTORY_SIZE;
int history_index = 0;
int h_ptr = 0;

void exe_prev_cmd(){
	char *command,ch,**args;
	printf("\nHistory feature : allows to exe prev executed cmds\n");
	printf("\tTo go up in cmd hist press: -> u\n");
	printf("\tTo go down in cmd hist press: -> d\n");
	printf("\tTo exe a cmd in cmd hist press: -> y\n");
	printf("\tTo exit press: -> q\n");
	while(1)
	{	
		printf("Enter choice : ");
		scanf(" %c",&ch);
		switch(ch){
			case 'u':
			            command = get_previous_command();
				    printf("## History - > %s", command);
				    break;
			case 'd':
			            command = get_next_command();
				    printf("## History - > %s", command);
				    break;
			case 'y':
			      	add_to_history(command);
			    	//preprocess line (replace env variables with actual value)
			    	command[strcspn(command, "\n")] = '\0'; // Remove trailing newline
			    	command = replace_env_var(command);
				// Parsing User Input
				args = parse_line(command);
				// Executing User Input
				execute_command(args);
				//free heap
				free(command);
				free(args);
				return ;
			case 'q':
				return;
			default : printf("Wrong choice\n");
				  return;
			
		}
	}

}


void add_to_history(char *line) {    
        // Check if history is NULL
    if (history == NULL) {
        // Allocate memory for the history buffer
        history = malloc(history_size * sizeof(char *));
        if (history == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0 ;i<history_size;i++) history[i] =NULL;
    }
    // Check if history_index exceeds history_size
    if (history_index >= history_size) {
        // Double the size of the history buffer
        int curr_hist = history_size;
        history_size *= 2;
        history = realloc(history, history_size * sizeof(char *));
        if (history == NULL) {
            fprintf(stderr, "Memory reallocation error\n");
            exit(EXIT_FAILURE);
        }
        for(int i = curr_hist;i<history_size;i++) history[i] =NULL;
    }

    // Allocate memory for the command to be added to history
    history[history_index] = malloc(strlen(line) + 1);
    if (history[history_index] == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Copy the command line to the allocated memory
    strcpy(history[history_index], line);

    // Update history index and history pointer
    history_index = (history_index + 1);// % history_size;
    h_ptr = history_index;
}

char *get_previous_command() {
    h_ptr--;
    if(h_ptr <0)h_ptr++;
    return history[h_ptr];
}

char *get_next_command() {
    h_ptr++;
    while(h_ptr >=history_size)h_ptr--;
    while(history[h_ptr] == NULL) h_ptr--;
    return history[h_ptr];
}

