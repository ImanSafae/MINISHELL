#include "minishell.h"

int	found_variable(char *env, char *var)
{
	
}

void	ft_unset(char *variable, char **env)
{
	int	variable_len;
	int	i;

	variable_len = ft_strlen(variable);
	i = 0;
	if (!variable)
		ft_putstr_fd("unset: not enough arguments\n", 2);
	while (env[i])
	{
		if (!ft_strncmp(variable, env[i]))
		i++;
	}
}
