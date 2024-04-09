
# Pb Shell

Pb Shell is a simple, yet powerful command-line shell designed for Unix-based systems. It aims to provide users with the ability to execute commands, handle file redirection, pipes, command chaining, and a history feature to navigate through previously executed commands.

## Features

- **Command Execution**: Execute standard Unix commands.
- **File Redirection**: Supports input (`<`), output (`>` and `>>`) redirection.
- **Pipes**: Use pipes (`|`) to chain commands.
- **Command Chaining**: Support for command chaining with `;`, `&&`, and `||`.
- **Command History**: Navigate through the history of executed commands with custom history management.
- **Batch Mode**: Give a file filled with commands as input to my shell
- **Env Support**: Supports Interpretation of Environment Variables

## Getting Started

To use Pb Shell, compile the project using make`or <a href="https://github.com/pb-dot/Deb_Packages">Click Here</a>.
Here is a step-by-step guide using make:

1. Clone this repository or download the source code.
2. Navigate to the source code directory.
3. Compile the code using the following command:

```bash
make
```

4. Run the shell:

```bash
./pbshell
```

You can also execute commands from a file by passing the filename as an argument:

```bash
./pbshell filename.txt
```

## Internal Commands

Pb Shell supports several internal commands:

- `cd`: Change the current directory.
- `clear`: Clear the console.
- `hist`: Access the command history. Navigate using `u` (up) and `d` (down), execute a command from history with `y`, and exit history mode with `q`.
- `exit`: Exit the shell.

## File Structure

- `main.c`: The entry point of the shell. It includes the main loop for command execution.
- `parse.c`: Contains the logic for parsing command line input into tokens.
- `pipe.c`: Handles command piping (`|`).
- `redir.c`: Manages file redirection (`<`, `>`, `>>`).
- `history.c`: Implements the command history feature.
- `exe.c`: Executes the commands, whether they are internal, involve redirection, pipes, or command chaining.
- `env.c`: Replaces environment variables with their values in commands.
- `chain.c`: Handles command chaining (`;`, `&&`, `||`).
- `header.h`: The header file with necessary includes and function declarations.

## Contributions

Contributions to Pb Shell are welcome! Feel free to fork the project, make changes, and submit pull requests.

