/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:21:03 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/27 10:45:34 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}

void	sigint(int sig)
{
	(void)sig;
	if (g_all.fd_to_close != -1)
		close(g_all.fd_to_close);
	printf("\n");
	if (!g_all.prompt)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (g_all.in_command == 1)
		g_all.exit_code = 130;
	else
		g_all.exit_code = 1;
}

void	sigquit(int sig)
{
	(void)sig;
	if (g_all.in_command == 1)
	{
		printf("Quit \n");
		g_all.exit_code = 131;
		return ;
	}
	g_all.exit_code = 0;
}

void	detect_signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}
