#include "shell.h"
#include "path_handling.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "builtin_commands.h"
/**
 * handle_env_command - Checks and handles the 'env' command
 * @command: The command to check
 * Return: 1 if 'env' command, 0 otherwise
 *
 * This function checks if the given command is the 'env' built-in command.
 * If it is, it prints the environment.
 */
int handle_env_command(char *command)
{
	if (strcmp(command, "env") == 0)
	{
		env_builtin();
		return (1);
	}
	return (0);
}

/**
 * handle_exit_command - Checks and handles the 'exit' command
 * @command: The command to check
 * Return: 1 if 'exit' command, 0 otherwise
 *
 * This function checks if the given command is the 'exit' built-in command.
 * If it is, it exits the shell. Returns 1 if 'exit' command, 0 otherwise.
 */
int handle_exit_command(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
		return (1); /* For clarity, even though it never reaches here */
	}
	return (0);
}

/**
 * create_process - Creates a process to execute a command
 * @cmd_path: The full path of the command
 * @args: Arguments for the command
 */
void create_process(char *cmd_path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execv(cmd_path, args) == -1)
		{
			perror("shell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		/* Error in forking */
		perror("shell");
	}
	else
	{
		/* Parent process */
		do	{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * execute_command - Executes a command with arguments
 * @args: Null-terminated list of arguments (command and parameters)
 *
 * This function first checks for built-in commands (like 'exit'). If it's
 * a regular command, it checks if the command exists in the PATH. If it
 * does, it creates a child process to execute the command. If the command
 * is not found, it prints an error message.
 */
void execute_command(char **args)
{
	char *cmd_path;

	if (args[0] == NULL)
		return; /* No command entered */

	if (handle_exit_command(args[0]))
		return; /* Exit command handled */
	if (handle_env_command(args[0]))
	return;
	cmd_path = find_command_in_path(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: Command not found\n", args[0]);
		return;
	}

	create_process(cmd_path, args);
	free(cmd_path);
}
