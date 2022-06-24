/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:21:03 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/24 15:57:25 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit(int sig)
{
	(void)sig;
	ft_putchar_fd(4, 1);
}

void	detect_signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}
