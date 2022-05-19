/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:18 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/19 19:45:19 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **env)
{
	int	i;
	int	env_length;

	i = 0;
	env_length = envlen(env);
	while (i < env_length)
	{
		ft_putstr_fd(env[i], 1);
		i++;
	}
}
