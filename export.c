/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:05 by itaouil           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/30 13:51:50 by itaouil          ###   ########.fr       */
=======
/*   Updated: 2022/05/30 15:21:21 by anggonza         ###   ########.fr       */
>>>>>>> 6a20befa22fdd42e005a0d4493f71ee2ab717e6b
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
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
=======
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
>>>>>>> 6a20befa22fdd42e005a0d4493f71ee2ab717e6b
}
