/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:22:39 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/14 23:51:51 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char **args)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	printf("%s\n", current_dir);
	free(current_dir);
}
