#include "header.h"

char *replace_env_var(char *command) {
    char *result = malloc(MAX_COMMAND_LENGTH); // Allocate memory for the result
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    memset(result, 0, MAX_COMMAND_LENGTH); // Initialize result buffer

    char *token;
    char *remaining = command;
    while ((token = strtok_r(remaining, " ", &remaining)) != NULL) {
        if (token[0] == '$') {
            char *env_var = token + 1; // Skip the '$' character
            char *env_value = getenv(env_var); // Get the value of the environment variable
            if (env_value != NULL) {
                strcat(result, env_value); // Append the value to the result
                strcat(result, " "); // Add a space after the value
            }
        } else {
            strcat(result, token); // Append the token to the result
            strcat(result, " "); // Add a space after the token
        }
    }

    return result;
}

