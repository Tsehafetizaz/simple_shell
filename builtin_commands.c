#include "builtin_commands.h"

/**
 * env_builtin - Prints the current environment
 */
void env_builtin(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
