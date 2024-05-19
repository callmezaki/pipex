# Pipex

## Description

Pipex is a C project that replicates the behavior of the Unix pipeline, enabling the chaining of commands with their respective inputs and outputs. This project aims to deepen understanding of process creation, management, and inter-process communication using pipes in Unix-like operating systems.

## Features

- Handles multiple command pipelines
- Supports standard input and output redirection
- Error handling for invalid commands and arguments

## Services

- **Command execution**: Executes given commands in sequence, passing output from one command as input to the next.
- **Pipe creation**: Manages the creation and usage of pipes to link commands.
- **Error handling**: Detects and manages errors in command execution and argument parsing.

## Getting Started

### Prerequisites

- GCC or any C compiler

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/callmezaki/pipex.git
   cd pipex
   ```

2. Compile the project:

   ```bash
   make
   ```

### Usage

Run Pipex with the following syntax:

```bash
./pipex file1 cmd1 cmd2 file2
```

- `file1`: The input file.
- `cmd1`: The first command to execute.
- `cmd2`: The second command to execute.
- `file2`: The output file.

Example:

```bash
./pipex infile "grep something" "wc -l" outfile
```

## Project Structure

- `src/`: Contains the source files.
- `Makefile`: Defines the build process for the project.
- `README.md`: Project documentation.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [GNU Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)
