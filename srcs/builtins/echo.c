/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:26:22 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/07 19:46:39 by itaouil          ###   ########.fr       */
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
	int	j;

	newtrail = 1;
	i = 0;
	j = 1;
	if (!args)
		echo("\n", 0);
	else
	{
		while (args[0][j] && !ft_strncmp(args[0], "-n", 2))
		{
			if (args[0][j] != 'n')
			{
				newtrail = 1;
				break ;
			}
			j++;
			if (j == ft_strlen(args[0]))
			{
				i++;
				newtrail = 0;
			}
		}
		while (args[i])
		{
			echo(args[i], newtrail);
			i++;
		}
	}
}
