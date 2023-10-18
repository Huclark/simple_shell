# Simple Shell Project
![alt text](https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.jpeg)

## Table of Contents
- [About](#about)
- [Objective](#objective)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Limitations](#limitations)
- [Contributing](#contributing)
- [License](#license)

## About
The `shell` is a command-line interface ( a program) that provides a user interface to interact with an operating system's kernel or execute commands. The `shell` acts as a bridge between the user and the operating system.
This project is a simple implementation of a `shell` in C. It illustrates how the shell works i.e. `read`, `parse`, `fork`, `exec` and `wait`. It is limited in functions as it is built to only meet the requirements given by ALX.

## Objectives
- Develop a custom `simple shell` that emulates the functionality
of the original `shell`.
- Deepen your understanding of the `C-programming language` and `Shell`.
- What is a `pid` and a `ppid`?
- How to manipulate the environment of the current process
- Difference between a function and a system call
- How to create processes
- Know the three prototypes of `main`
- How the shell uses `PATH` to find programs.
- How to execute another program with the `execve` system call
- How to suspend the execution of a process until one of its children terminates
- What is `EOF` / “end-of-file”?

## Features
### List of allowed functions and system calls
- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `getpid` (man 2 getpid)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (__xstat) (man 2 stat)
- `lstat` (__lxstat) (man 2 lstat)
- `fstat` (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)

## Prerequisites
The only prerequisite is to clone this repo. However, you need a good understanding of the following:
- [Pointers & Arrays]
- [Structures & Typedef]
- [Function Pointers]
- [Command-line arguments (Argv & Argc)]
- [Dynamic Memory Allocation (Malloc)]
- [Process Identifier (PID) & Parent Process Identifier (PPID)]
- [fork()]
- [execve()]
- [wait()]
- [getline()]
- [strtok]

## Installation
1. Clone the repository:

   ```bash
	https://github.com/Huclark/simple_shell.git

2. Use `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh` to compile.

3. Use `./hsh` to run.


## Limitations
This is a school project and it is built to meet the requirements of the project. It has many limitations including:
- Only built-ins are `cd`, `exit`, `env`

## Contributions
This is a team project with the following contributors:
  - [Huclark Vanderpuye](https://github.com/Huclark): vhuclark@gmail.com <br/>
  - [Charles Anderson](https://github.com/Charles130-Anderson): andersonoyoo034@gmail.com

Since this is a team project for ALX SE Progamme, we won't be accepting any pull requests. However, please feel free to make or suggest any changes that would make the whole code run better. See [AUTHORS](AUTHORS) for our emails to reach us.

## License
This code is in the public domain (see [UNLICENSE](UNLICENSE) for more details). This means you can use, modify, and distribute it without any restriction. We appreciate, but don't require, acknowledgement in derivative works.
