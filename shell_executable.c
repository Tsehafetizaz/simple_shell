#include "shell.h"

/**
 * execute_command - Executes a single command
 * @args: Null-terminated list of arguments (the command and its parameters)
 *
 * This function creates a child process using fork and executes
 * the command using execve. It handles only single-word commands
 * without arguments. The parent process waits for the child process
 * to finish execution.
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
	{
		return;
	}

	pid = fork();
	if (pid == 0)
{
		/* Child process */
		if (execve(args[0], args, environ) == -1)
{
			perror("shell");
}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
{
		/* Forking error */
		perror("shell");
	} else
{
		/* Parent process waits for child to finish */
		do	{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
