/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:21:03 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/26 12:38:48 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	if (g_all.fd_to_close != -1)
		close(g_all.fd_to_close);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_all.exit_code = 130;
}

void	sigquit(int sig)
{
	(void)sig;
	close(0);
	return ;
}

void	detect_signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}
