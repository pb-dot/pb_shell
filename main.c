#include "header.h"


int main(int argc, char ** argv) {

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("\nWelcome to Pb Shell\n");
    printf("\tEnter cmds only after seeing the ## prompt\n");
    printf("\tInternal Cmds supported are cd | clear | hist | exit\n\n");


    if (argc == 2) {// If a filename is provided, execute commands from the file
    	printf("Executing contents of input file %s\n",argv[1]);
        execute_commands_from_file(argv[1]);
        printf("Finished Executing Contents of ur input file\n");
    }
    
    
    char *line;
    char * cwd=NULL;
    char **args;
    ssize_t buffer_size;
    
   while (1){
   	cwd = getcwd(cwd,0);
        printf("\n%s ## ",cwd);
        // Reading User Input
        line = NULL;
    	buffer_size = 0;
    	getline(&line, &buffer_size, stdin);

    	// Store the command in history
        add_to_history(line);   	
    	//preprocess line (replace env variables with actual value)
    	line[strcspn(line, "\n")] = '\0'; // Remove trailing newline
    	line = replace_env_var(line);    	
    	// Parsing User Input
        args = parse_line(line);
        // Executing User Input
        execute_command(args);
	//free heap
        free(line);
        free(args);
        free(cwd);
        cwd=NULL;
    }
    
    return EXIT_SUCCESS;
}

// Function to read commands from a file and execute them
void execute_commands_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        line[strcspn(line, "\n")] = '\0'; // Remove trailing newline

        // Replace environment variables in the command line
        line = replace_env_var(line);

        // Parse the command line into arguments
        char **args = parse_line(line);

        // Execute the command
        execute_command(args);

        // Free allocated memory for arguments
        free(args);
    }

    // Free allocated memory for the line
    free(line);

    // Close the file
    fclose(file);
}


