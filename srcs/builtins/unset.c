/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:44:54 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/26 15:56:14 by itaouil          ###   ########.fr       */
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
		&& (int)ft_strlen(_element) == len)
		return (1);
	return (0);
}

static int	check_unset(char *var, t_list *tmp)
{
	if (found_variable(tmp, var))
	{
		g_all.env = (g_all.env)->next;
		ft_lstdelone(tmp, &empty_env_element);
		return (1);
	}
	return (0);
}

static void	remove_from_env(char *var, t_list *tmp, t_list *tmp2)
{
	tmp = g_all.env;
	if (check_unset(var, tmp))
		return ;
	while (tmp->next)
	{
		if (found_variable(tmp->next, var))
		{
			if (tmp->next->next)
			{
				tmp2 = tmp->next->next;
				ft_lstdelone(tmp->next, &empty_env_element);
				tmp->next = tmp2;
				return ;
			}
			else
			{
				ft_lstdelone(tmp->next, &empty_env_element);
				tmp->next = NULL;
				return ;
			}
		}
		else
			tmp = tmp->next;
	}
}

static void	exec_unset(char *variable)
{
	t_list	*tmp;
	t_list	*tmp1;
	t_list	*tmp2;

	tmp = g_all.env;
	tmp1 = NULL;
	tmp2 = NULL;
	if (!variable)
		return ;
	while (tmp)
	{
		if (found_variable(tmp, variable))
		{
			remove_from_env(variable, tmp1, tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		exec_unset(args[i]);
		i++;
	}
}
