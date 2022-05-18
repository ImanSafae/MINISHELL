#include "minishell.h"

int	envlen(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

t_list	*create_env(char **envp)
{
	t_list	*env;
	t_list	*tmp;
	int		i;

	env = malloc(sizeof(t_list) * (envlen(envp) + 1));
	i = 1;
	env = ft_lstnew(envp[0]);
	tmp = env;
	while (i < envlen(envp))
	{
		ft_lstadd_back(&env, ft_lstnew(envp[i]));
		i++;
	}
	return (env);
}
