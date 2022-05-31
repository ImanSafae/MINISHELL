/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:18 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/30 17:56:43 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list **env)
{
	t_list	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (((t_env *)tmp->content)->value)
		{
			ft_putstr_fd(((t_env *)tmp->content)->variable, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(((t_env *)tmp->content)->value, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
}
