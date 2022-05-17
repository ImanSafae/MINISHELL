#include "minishell.h"

void	ft_env(char **env)
{
	int	i;
	int	env_length;

	i = 0;
	env_length = envlen(env);
	while (i < env_length)
	{
		ft_putstr_fd(env[i], 1);
		i++;
	}
}
