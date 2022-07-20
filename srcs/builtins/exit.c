/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:17:32 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/20 22:12:05 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_exit(char **code)
{
	int	i;

	i = 0;
	if (!code)
	{
		printf("exit\n");
		exit(g_all.exit_code);
	}
	while (code && code[0] && code[0][i])
	{
		printf("ca arrive ici\n");
		if (!ft_isdigit(code[0][i]))
		{
			if (ft_isspace(code[0][i]))
				send_error(EXIT, TOO_MANY_ARGS, code[0]);
			else
				send_error(EXIT, NUM, code[0]);
			break ;
		}
		i++;
	}
	printf("exit\n");
	// il faut aussi envoyer un signal pour terminer le process
	exit(ft_atoi(code[0]));
}

void	ft_exit(char **args)
{
	if (args)
	{
		printf("il y a des arguments: %s\n", args[0]);
	}
	if (args && tab_length(args) > 1)
	{
		send_error(EXIT, TOO_MANY_ARGS, NULL);
		exit(EXIT_FAILURE);
	}
	exec_exit(args);
}
