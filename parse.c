#include "header.h"
char **parse_line(char *line) {
    int buffer_size = BUFFER_SIZE, position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMITER);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= buffer_size) {
            buffer_size += BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITER);
    }
    tokens[position] = NULL;
    
    //printing the tokens
    //for(int i =0 ; tokens[i]!= NULL ; i++)
    //	printf("@%s@\n",tokens[i]);
    
    return tokens;
}

