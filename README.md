# MINISHELL

Minishell is a 42 School project that involves creating a simple UNIX shell, adhering to the specifications provided in the subject. The project is a deep dive into process management, system calls, and memory management.
Features:

- Implements a subset of Bash functionality as described in the subject.
- Supports the execution of basic commands, with proper argument handling.
- Includes built-in commands (e.g., cd, echo, pwd, etc.) with behavior mimicking Bash.
- Handles input redirection (<), output redirection (>), pipes (|), and environment variables ($VAR).
- Interactive mode using readline() for user input.

### Requirements

- No memory leaks: All dynamically allocated resources in your code must be properly freed.
- Reference Bash: When in doubt about expected behavior, Bash is the standard.

### How to Run

- Clone the repository:
```
git clone <repository-url>  
cd minishell  
```

- Compile the project:
```
make  
```

- Run the shell:
```
    ./minishell  
```
