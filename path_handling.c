#include "path_handling.h"
#include "shell.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

/**
 * find_command_in_path - Finds the full path of a command
 * @cmd: The command to find
 * Return: Full path of the command or NULL if not found
 *
 * This function checks if the command is an absolute path and exists.
 * If it is not an absolute path, it searches for the command directories
 * specified by the PATH environment variable.
 */
char *find_command_in_path(char *cmd)
{
	struct stat st;
	char *path, *path_copy, *token, *full_cmd;

	/* All variable declarations at the start of the block for C89 compliance */
	path = getenv("PATH");
	path_copy = strdup(path);
	token = strtok(path_copy, ":");
	full_cmd = NULL;

	/* Check if cmd is an absolute path and exists */
	if (cmd[0] == '/' && stat(cmd, &st) == 0)
	{
		free(path_copy);
		return (strdup(cmd)); /* Return the command itself */
	}

	/* Search in PATH if cmd is not an absolute path */
	while (token)
	{
		full_cmd = malloc(strlen(token) + strlen(cmd) + 2);
		sprintf(full_cmd, "%s/%s", token, cmd);
		if (stat(full_cmd, &st) == 0)
{
			free(path_copy);
			return (full_cmd); /* Return the full path */
		}
		free(full_cmd);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL); /* Command not found */
}
