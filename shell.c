#include <stdlib.h>     /* For exit, malloc, free */
#include <unistd.h>     /* For fork, execve, getpid */
#include <sys/types.h>  /* For pid_t */
#include <sys/wait.h>   /* For waitpid */
#include <stdio.h>      /* For perror, getline */

extern char **environ;   /* External environment variable */

int main(void)
{
	char *cmd = NULL;    /* Buffer for command */
	size_t len = 0;      /* Length of the buffer */
	ssize_t nread;       /* Number of characters read */
	pid_t pid;           /* Process ID */
	int status;          /* Child process status */

	while (1)
	{
		/* Display a simple prompt */
		write(STDOUT_FILENO, "Simple shell>  ", 14);

		/* Read a line from stdin */
		nread = getline(&cmd, &len, stdin);
		if (nread == -1)
		{
			/* If getline fails, check for EOF and exit or print error */
			if (feof(stdin))
			{
				free(cmd);
				exit(EXIT_SUCCESS);  /* Exit on EOF (Ctrl+D) */
			}
			else
			{
				perror("Error reading command");
				free(cmd);
				continue;
			}
		}

		/* Remove newline character from end of input */
		if (cmd[nread - 1] == '\n')
		{
			cmd[nread - 1] = '\0';
		}

		/* Fork a new process */
		pid = fork();
		if (pid < 0)
		{
			/* Fork failed */
			perror("Fork failed");
			continue;
		}

		if (pid == 0)
		{
			/* Child process */
			char *argv[2];  /* Command argument array */
			argv[0] = cmd;  /* Set command to execute */
			argv[1] = NULL; /* Null-terminate the argument array */

			/* Execute the command */
			if (execve(cmd, argv, environ) == -1)
			{
				perror("Execve failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process */
			/* Wait for the child process to finish */
			waitpid(pid, &status, 0);
			free(cmd);
			cmd = NULL;
		}
	}

	/* Free allocated memory */
	free(cmd);
	return (0);
}
