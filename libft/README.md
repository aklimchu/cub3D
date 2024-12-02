# Libft - Personal C Library

Libft is a foundational project developed at Hive Helsinki, part of the 42 Network. The objective is to recreate essential functions from the C standard library, providing a deeper understanding of their inner workings and preparing for future projects where standard functions may be restricted. I have augmented the standard project base with some of my own additions, e.g. the memlist-functions which simplify manual memory management.

## Features

- **Standard Library Functions**: Re-implemented functions for string manipulation, memory management, and character checks.
- **Additional Utilities**: Custom functions to enhance functionality beyond the standard library.
- **Linked List Operations**: Functions to create and manage linked lists, facilitating dynamic data structures.

## Project Structure

The project is organized as follows:

- `ft_printf/`: Implementation of the `ft_printf` function, a custom version of the standard `printf`.
- `get_next_line/`: Function to read a line from a file descriptor, handling multiple file descriptors simultaneously.
- `include/`: Header files containing function prototypes and necessary macros.
- `memlist/`: Memory management utilities, including custom allocation and deallocation functions.
- Source files (`ft_*.c`): Individual function implementations covering various utilities.

## Build

To compile the library, navigate to the project directory and run:

```bash
make
```
This command generates the libft.a static library, which can be linked to other projects.

## Usage
Include the `libft.h`, `ft_printf.h`, `get_next_line.h` or `memlist.h` header in your project:
```C
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "memlist.h"

```
Link the compiled library during the compilation of your project:
```bash
gcc your_program.c path/to/libft.a -o your_program -I path/to/libft/include
```

## Acknowledgements
This project is part of the Hive Helsinki curriculum, inspired by the 42 Network's emphasis on peer-to-peer learning and hands-on projects.