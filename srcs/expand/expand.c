/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:30:31 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/14 17:24:43 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable(char **value)
{
	t_list	*tmp;

	tmp = g_all.env;
	if (!ft_strncmp(*value, "?", 1) && ft_strlen(*value) == 1)
	{
		free(*value);
		*value = ft_itoa(g_all.exit_code);
		return ;
	}

	while (tmp->next)
	{
		if (ft_strlen(*value) == ft_strlen(((t_env *)(tmp->content))->variable))
		{
			if (!ft_strncmp(*value, ((t_env *)(tmp->content))->variable,
				ft_strlen(*value)))
			{
				free(*value);
				*value = ft_strdup(((t_env *)(tmp->content))->value);
				return ;
			}
		}
		tmp = tmp->next;
	}
}
