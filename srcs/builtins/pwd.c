#include "../minishell.h"

void	ft_pwd(char **args)
{
	char	*current_dir;

	if (args != NULL)
	{
		send_error(PWD, TOO_MANY_ARGS, NULL);
		exit(EXIT_FAILURE);
	}
	current_dir = getcwd(NULL, 0);
	printf("%s\n", current_dir);
	free(current_dir);
}
