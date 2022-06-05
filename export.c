/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:05 by itaouil           #+#    #+#             */
/*   Updated: 2022/06/05 17:39:29 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_entry(char *var, char *value)
{
	t_env	*new_entry;

	new_entry = malloc(sizeof(t_env));
	new_entry->variable = ft_strdup(var);
	if (value)
		new_entry->value = ft_strdup(value);
	else
		new_entry->value = NULL;
	return (new_entry);
	// ft_lstadd_back(env, ft_lstnew(&new_entry));
}

void	ft_export(t_list **env, char *var, char *value)
{
	if (!var)
		print_env_in_ascii_order(*env);
	else
	{
		ft_lstadd_back(env, ft_lstnew(new_env_entry(var, value)));
	}
	
}
