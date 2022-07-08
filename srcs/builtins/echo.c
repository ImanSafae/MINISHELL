/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:26:22 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/08 01:48:56 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo(char **args, int newtrail)
{
	int	i;

	i = 0;
	if (!newtrail)
		i++;
	while (i < tab_length(args) - 1)
	{
		printf("%s ", args[i]);
		i++;
	}
	if (!newtrail)
		printf("%s", args[i]);
	else
		printf("%s\n", args[i]);
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
	if (!(*args))
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
		echo(args, newtrail);
	}
}
