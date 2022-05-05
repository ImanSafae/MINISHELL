#include "minishell.h"

int	envlen(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**create_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * envlen(envp));
	while (envp[i])
	{
		env[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		env[i] = envp[i];
		i++;
	}
	return (env);
}
