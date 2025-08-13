# Minishell

A custom implementation of a shell, similar to bash. This project is part of the 42 school curriculum.

## Features

This minishell supports a range of features to provide a user-friendly command-line experience:

- **Command Execution**: Execute system commands with arguments.
- **Built-in Commands**:
  - `echo` with the `-n` option
  - `cd` with relative or absolute paths
  - `pwd` to display the current working directory
  - `export` to manage environment variables
  - `unset` to remove environment variables
  - `env` to display the environment variables
  - `exit` to terminate the shell
- **Pipes (`|`)**: Chain multiple commands together, passing the output of one to the input of another.
- **Logical Operators (`&&` and `||`)**: Execute commands conditionally based on the success or failure of the previous command.
- **Redirections**:
  - `>`: Redirect output to a file.
  - `<`: Redirect input from a file.
  - `>>`: Append output to a file.
  - `<<`: Here document for multi-line input.
- **Subshells (`(...)`)**: Group commands to be executed in a separate child process.
- **Environment Variables**: Expand environment variables (e.g., `$HOME`).
- **Wildcards (`*`)**: Use wildcards to match filenames in the current directory.
- **Quotes**: Handles single (`'`) and double (`"`) quotes to manage string literals and expansions.

## Installation

### Prerequisites

This project requires the `readline` library to be installed on your system.

- **On macOS (using Homebrew):**
  ```sh
  brew install readline
  ```

- **On Debian/Ubuntu (using apt):**
  ```sh
  sudo apt-get update && sudo apt-get install libreadline-dev
  ```

### Compilation

1.  **Clone the repository:**
    ```sh
    git clone <repository_url>
    cd minishell
    ```

2.  **Compile the project:**
    The included `Makefile` is configured for the 42 school environment. If you are compiling on a different system, you may need to update the `CFLAGS` in the `Makefile` to point to your `readline` installation.

    For example, on macOS with Homebrew, you might change:
    `-L/goinfre/$(USER)/homebrew/opt/readline/lib -I/goinfre/$(USER)/homebrew/opt/readline/include`
    to:
    `-L$(brew --prefix readline)/lib -I$(brew --prefix readline)/include`

    Once the `Makefile` is configured, run:
    ```sh
    make
    ```
    This will create the `minishell` executable.

## Usage

To start the shell, run the compiled executable from the root of the project directory:

```sh
./minishell
```

You will be greeted with a new prompt, ready to accept your commands. To exit the shell, type `exit` or press `Ctrl-D`.
