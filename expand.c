/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:30:31 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/27 15:26:58 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_all	g_all;

void	expand_variable(char **value, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	if (!ft_strncmp(*value, "?", 1))
		*value = ft_itoa(g_all.exit_code);
	while (tmp->next)
	{
		if (ft_strlen(*value) == ft_strlen(((t_env *)(tmp->content))->variable))
			if (!ft_strncmp(*value, ((t_env *)(tmp->content))->variable,
				ft_strlen(*value)))
				*value = ((t_env *)(tmp->content))->value;
		tmp = tmp->next;
	}
}
