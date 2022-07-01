#include "minishell.h"

static void	parsing_errors(int error, char *arg)
{
	if (error == OPEN_QUOTE)
		printf("Error : unclosed quote\n");
	else if (error == WRONG_FILE)
		printf("%s: No such file or directory\n", arg);
	else if (error == NEAR)
		printf("parse error near '%s'\n", arg);
	// exit(EXIT_FAILURE);
}

static void	exit_errors(int error, char *arg)
{
	printf("exit: ");
	if (error == NUM)
		printf("%s : numeric argument required\n", arg);
	else if (error == TOO_MANY_ARGS)
		printf("too many arguments\n");
}

void	send_error(int function, int error, char *arg)
{
	printf("minishell-obama: ");
	if (function == EXIT)
		exit_errors(error, arg);
	else if (function == PARSING)
		parsing_errors(error, arg);
}
