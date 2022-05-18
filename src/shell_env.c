#include "minishell.h"

int	envlen(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

t_list	**create_env(char **envp)
{
	t_list	**env;
	t_list	*tmp;
	int		i;

	tmp = (*env);
	env = malloc(sizeof(t_list) * envlen(envp));
	i = 0;
	while (i < envlen(envp))
	{
		tmp->content = envp[i];
		tmp = tmp->next;
		i++;
	}
	return (env);
}
