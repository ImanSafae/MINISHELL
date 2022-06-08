/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:03 by itaouil           #+#    #+#             */
/*   Updated: 2022/06/08 16:18:53 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_element(void *element)
{
	element = NULL;
}

int	envlen(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

t_env	*add_var_to_env(char *line)
{
	t_env	*element;
	char	**env_line;

	element = malloc(sizeof(t_env));
	env_line = ft_split(line, '=');
	element->variable = ft_strdup(env_line[0]);
	element->value = ft_strdup(env_line[1]);
	free_tab(env_line);
	return (element);
}

t_list	*create_env(char **envp)
{
	t_list	*env;
	//t_list	*tmp;
	int		i;

	i = 1;
	env = ft_lstnew(add_var_to_env(envp[0]));
	while (i < envlen(envp))
	{
		ft_lstadd_back(&env, ft_lstnew(add_var_to_env(envp[i])));
		i++;
	}
	return (env);
}
