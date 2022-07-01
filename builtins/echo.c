/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:26:22 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/01 15:36:56 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char *arg, int newtrail)
{
	if (!newtrail)
		printf("%s", arg);
	else
		printf("%s\n", arg);
	g_all.exit_code = 0;
}
