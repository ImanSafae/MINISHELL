#include "minishell.h"

void	ft_exit(char *code)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (!ft_isdigit(code[i]))
		{
			if (ft_isspace(code[i]))
				send_error(EXIT, TOO_MANY_ARGS, code);
			else
				send_error(EXIT, NUM, code);
		}
		i++;
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}