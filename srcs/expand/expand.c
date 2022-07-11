/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:30:31 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/12 01:26:34 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable(char **value)
{
	t_list	*tmp;

	tmp = g_all.env;
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
