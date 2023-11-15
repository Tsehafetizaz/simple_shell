#include "shell.h"
#include <signal.h>

/**
 * sigint_handler - Signal handler for SIGINT (Ctrl+C)
 * @sig: Signal number (unused in this handler)
 *
 * This function handles the SIGINT signal. It writes a message and
 * exits the shell when Ctrl+C is pressed.
 */
void sigint_handler(int sig __attribute__((unused)))
{
	write(STDOUT_FILENO, "\nExiting shell...\n", 18);
	exit(EXIT_SUCCESS);
}

/**
 * main - Entry point of the shell program
 *
 * The main function sets up a signal handler for SIGINT and then
 * enters a loop where it continually reads and executes commands
 * from the user. The loop terminates on EOF (Ctrl+D).
 * Return: 0 on normal exit, or an error code on failure.
 */
int main(void)
{
	char *line;
	char **args;
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	while (1)
{
		printf("$ ");
		line = read_line();
		if (!line || feof(stdin))
{
			if (line)
			{
				free(line);
			}
			break;
		}
		args = split_line(line);
		execute_command(args);
		free(line);
		free(args);
	}
	return (0);
}
