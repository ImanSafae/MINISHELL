/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:17:32 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/05 20:58:26 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_exit(char *code)
{
	int	i;

	i = 0;
	if (!code)
		return (g_all.exit_code);
	while (code[i])
	{
		if (!ft_isdigit(code[i]))
		{
			if (ft_isspace(code[i]))
				send_error(EXIT, TOO_MANY_ARGS, code);
			else
				send_error(EXIT, NUM, code);
		}
		i++;
	}
	printf("exit\n");
	// il faut aussi envoyer un signal pour terminer le process
	exit(EXIT_SUCCESS); 
}

void	ft_exit(char **args)
{
	if (tab_length(args) > 1)
	{
		send_error(EXIT, TOO_MANY_ARGS, NULL);
		exit(EXIT_FAILURE);
	}
	exec_exit(args[0]);
}
