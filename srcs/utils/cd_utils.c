/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:23:26 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/26 15:37:47 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_variable_in_env(char *str)
{
	t_list	*tmp;

	tmp = g_all.env;
	while (tmp->next)
	{
		if (ft_strlen(str) == ft_strlen(((t_env *)(tmp->content))->variable))
		{
			if (!ft_strncmp(str, ((t_env *)(tmp->content))->variable,
				ft_strlen(str)))
				return (((t_env *)(tmp->content))->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
