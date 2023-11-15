#include "shell.h"

/**
 * read_line - Reads a line from stdin
 * Return: The line read from stdin
 *
 * This function reads a line of input from standard input using getline
 * and returns the line to the caller.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;

	getline(&line, &len, stdin);
	return (line);
}

/**
 * split_line - Splits a line into a command and arguments
 * @line: The line to split
 * Return: Array containing the command and NULL as the second element
 *
 * This function splits the given line into command and arguments.
 * Since the shell is designed to handle single-word commands without
 * arguments, it only extracts the first word and ignores the rest.
 */
char **split_line(char *line)
{
	char **args = malloc(2 * sizeof(char *));
	char *token;

	if (!args)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	args[0] = token;
	args[1] = NULL;
	return (args);
}
