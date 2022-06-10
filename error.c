#include "minishell.h"

static void	exit_errors(int error, char *arg)
{
	printf("exit: ");
	if (error == NUM)
		printf("%s : numeric argument required\n");
	else if (error == TOO_MANY_ARGS)
		printf("too many arguments\n");
}

void	send_error(int function, int error, char *arg)
{
	printf("minishell-obama :");
	if (function == EXIT)
		exit_errors(error, arg);
}
