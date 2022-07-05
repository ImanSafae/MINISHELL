/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:26:22 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/05 20:22:43 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo(char *arg, int newtrail)
{
	if (!newtrail)
		printf("%s", arg);
	else
		printf("%s\n", arg);
	g_all.exit_code = 0;
}

void	ft_echo(char **args)
{
	int	newtrail;
	int	i;

	newtrail = 0;
	i = 1;
	if (!args)
		echo("\n", 0);
	else
	{
		if (!ft_strncmp(args[0], "-n", 2) && ft_strlen(args[0]) == 2)
			newtrail = 1;
		while (args[i])
		{
			echo(args[i], newtrail);
			i++;
		}
	}
}
