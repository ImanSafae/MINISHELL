/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:05 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/30 13:51:50 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_env_entry(t_list **env, char *var, char *value)
{
	t_env *entry;

	entry = malloc(sizeof(t_env));
	entry->variable = var;
	entry->value = value;
	ft_lstadd_back(env, ft_lstnew(entry));
}

void	ft_export(t_list **env, char *var)
{
	if (!var)
		print_env_in_ascii_order(*env);
// 	else
// 	{
		
// 	}
}
