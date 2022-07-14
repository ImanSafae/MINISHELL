/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:18 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/14 16:47:52 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **args)
{
	t_list	*tmp;

	tmp = g_all.env;
	if (args != NULL)
	{
		send_error(ENV, TOO_MANY_ARGS, NULL);
		exit(EXIT_FAILURE);
	}
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
