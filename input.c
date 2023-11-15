#include "shell.h"

/**
 * read_line - Reads a line from stdin
 * Return: The line read from stdin
 *
 * This function reads a line of input from standard input using getline
 * and returns the line to the caller. It dynamically allocates a buffer
 * to hold the input line, which should be freed by the caller.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		if (feof(stdin))
		{
			/* End of file (Ctrl+D) */
			exit(EXIT_SUCCESS);
		}
		else
		{
			/* Some other error occurred */
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * split_line - Splits a line into command and arguments
 * @line: The line to split
 * Return: Null-terminated array of pointers to each argument
 *
 * This function splits the given line into command and arguments using
 * space as a delimiter. It dynamically allocates an array to hold the
 * pointers to the command and its arguments and returns this array.
 * The array is terminated by a NULL pointer.
 */
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}
