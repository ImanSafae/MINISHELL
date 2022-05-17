#include "minishell.h"

int	found_variable(char *env, char *var)
{
	int	len;

	len = ft_strlen(var);
	if (!ft_strncmp(env, var, len) && !ft_strncmp(env[len], '=', 1))
		return (1);
	else
		return (0);
}

void	remove_from_env(char ***env, int i)
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
		if (found_variable(env[i], variable) == 1)
		{
			remove_from_env(&env, i);
			return ;
		}
		i++;
	}
}
