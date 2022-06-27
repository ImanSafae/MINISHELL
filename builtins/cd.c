/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:45:04 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/27 15:27:44 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_all	g_all;

void	cd(char *arg)
{
	if (!arg)
	{
		if (chdir(getenv("HOME")) == -1)
			g_all.exit_code = 127;
	}
	else
	{
		if (chdir(arg) == -1)
			g_all.exit_code = 127;
	}
}
