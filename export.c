/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:05 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/30 15:21:21 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_env_entry(t_list **env, char *var, char *value)
{
	t_env	new_entry;

	new_entry.variable = var;
	new_entry.value = value;
	ft_lstadd_back(env, ft_lstnew(&new_entry));
}

void	ft_export(t_list **env, char *var, char *value)
{
	if (!var)
		print_env_in_ascii_order(*env);
	else
	{
		new_env_entry(env, var, value);
	}
}
