*This project has been created as part of the 42 curriculum by gtomasin.*

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor and returns
one line per call.

The returned line includes the newline character (`\n`) when one is present
in the input. If the file ends without a newline, the last line is returned
without adding one.

The project explores:
- Reading data with `read`.
- Dynamic memory allocation and memory ownership.
- Static variables and persistence between function calls.
- Buffer management and string manipulation.
- Handling end-of-file and errors.

### Prototype

```c
char	*get_next_line(int fd);
```

The function returns:
- An allocated line when data is available.
- `NULL` when there is no more data or an error occurs.

The caller must free each returned line.

This implementation uses one static buffer and is intended for reading
one file descriptor at a time. It does not implement the multiple-file-
descriptor bonus.

## Instructions

### Requirements

- A C compiler, such as `cc`.
- A POSIX environment providing `read`, such as Linux.
- The following files:
  - `get_next_line.c`
  - `get_next_line_utils.c`
  - `get_next_line.h`

No additional library installation is required.

### Compilation

The project provides a function rather than a standalone executable.
To compile its source files without a test program:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    -c get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` controls the maximum number of bytes requested by each
`read` call. It does not limit the length of a returned line.

If no value is provided during compilation, the header defines a
default value of `42`.

### Usage example

Create a `main.c` file:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Compile and run:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    main.c get_next_line.c get_next_line_utils.c -o gnl

./gnl example.txt
```

This example stops when `get_next_line` returns `NULL`. The interface does
not distinguish end-of-file from a reading or allocation error.

## Algorithm and justification

### General approach

The implementation accumulates data in a static string called `keep`.
This string stores bytes that have been read but not yet returned.

A static variable is useful because a single `read` call can retrieve
several lines. The bytes after the first newline must remain available
for the next call to `get_next_line`.

### 1. Read and accumulate data

If `keep` already contains a newline, the function can extract a line
without reading more data.

Otherwise, `read_line` reads chunks of up to `BUFFER_SIZE` bytes.
Each successful read is terminated with `'\0'`, allowing the temporary
buffer to be used by the string utilities.

The new bytes are appended to `keep` using `ft_strjoin`.
The previous allocation is freed after concatenation.

Reading stops when:
- A newline is found.
- `read` returns `0`, indicating end-of-file.
- A reading or allocation error occurs.

After checking the initial contents of `keep`, the reading loop only
needs to search the newly read chunk for a newline.

### 2. Extract a line

`get_line` finds the first newline or the end of the accumulated string.

It allocates a separate string for the returned line and copies the
appropriate characters into it, including the newline when present.

### 3. Preserve the remaining data

The custom `ft_strchr` helper allocates a copy of the characters after
the first newline.

Unlike the standard `strchr`, this helper does not return a pointer
inside the original string. It returns an independently allocated
suffix, or `NULL` when there is no remaining content.

The old `keep` allocation is freed and replaced with this suffix.

### 4. Handle end-of-file and errors

The `eof` helper frees the temporary reading buffer and finalizes the
current operation.

If data remains at end-of-file, it is returned as the last line.
No newline is added if it was absent from the input.

When no data remains, or when a reading error occurs, the stored
allocation is freed and reset to `NULL`.

### Why this algorithm?

This approach keeps the implementation straightforward:
- The static buffer preserves unread content between calls.
- Reading, extraction, and cleanup have separate responsibilities.
- Returned lines have independent allocations.
- Lines can be longer than `BUFFER_SIZE`.
- It uses `read`, `malloc`, and `free` without requiring `realloc`.

### Complexity and limitations

The main trade-off is repeated concatenation.

For a long line of length `n` with `BUFFER_SIZE=1`, each append copies
the previously accumulated content. The total copying work is
proportional to:

```text
1 + 2 + 3 + ... + n
```

The worst-case running time is therefore O(n²) for this case.
Searching only the newly read chunk avoids repeated newline scans,
but does not remove the concatenation cost.

A local test reported a timeout for a 100,000-character line without
a newline when using `BUFFER_SIZE=1`. Performance on this case remains
a known limitation.

A possible improvement would be to track the buffer length and
capacity, growing its capacity geometrically instead of allocating
an exact-sized string for every append.

Memory usage is proportional to the accumulated data, with temporary
additional allocations during concatenation and line extraction.

## Testing

Useful test cases include:
- An empty file.
- A file containing only a newline.
- A single line with or without a final newline.
- Several consecutive empty lines.
- Multiple lines read within one buffer.
- Lines longer than `BUFFER_SIZE`.
- Invalid file descriptors.
- Very long lines with small buffer sizes.

Compile with different buffer sizes to check behavior:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
    main.c get_next_line.c get_next_line_utils.c -o gnl
```

Replace `1` with other values, such as `42` or `1024`.

## Resources

### Documentation

The following references can be consulted through the local manual
system, provided the corresponding manual pages are installed:

- `man 2 read`: reading from file descriptors, return values, and errors.
- `man 3 malloc`: dynamic memory allocation.
- `man 3 free`: releasing allocated memory.
- `man 2 open`: opening files and obtaining file descriptors.
- `man 2 close`: closing file descriptors.
- `man 3 strchr`: standard character-search behavior, for comparison
  with this project's custom helper.

Other references:
- The project subject: required behavior and project constraints.
- The 42 Norm: coding-style requirements.
- *The C Programming Language*, Brian W. Kernighan and Dennis M. Ritchie:
  pointers, arrays, storage duration, and memory management.

### Use of AI

AI assistance was used to help generating this README.
