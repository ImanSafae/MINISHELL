/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:44:54 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/12 01:21:24 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	found_variable(t_list *element, char *variable)
{
	char	*_element;
	int		len;

	_element = ((t_env *)(element->content))->variable;
	len = ft_strlen(variable);
	if (!ft_strncmp(_element, variable, len)
		&& !_element[len + 1])
		return (1);
	return (0);
}

static void	remove_from_env(char *var)
{
	t_list	*tmp;

	tmp = g_all.env;
	if (found_variable(tmp, var))
	{
		g_all.env = (g_all.env)->next;
		ft_lstdelone(tmp, &empty_env_element);
		return ;
	}
	while (tmp->next)
	{
		if (found_variable(tmp->next, var))
		{
			ft_lstdelone(tmp->next, &empty_env_element);
			tmp->next = tmp->next->next;
			return ;
		}
		else
			tmp = tmp->next;
	}
}

static void	exec_unset(char *variable)
{
	t_list	*tmp;

	tmp = g_all.env;
	if (!variable)
		return ;
	while (tmp)
	{
		if (found_variable(tmp, variable))
		{
			remove_from_env(variable);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
	{
		printf("error\n");
		send_error(UNSET, NOT_ENOUGH_ARGS, NULL);
	}
	while (args && args[i])
	{
		exec_unset(args[i]);
		i++;
	}
}
