/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:37:20 by anggonza          #+#    #+#             */
/*   Updated: 2022/05/05 16:20:49 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_sort_env(char **env)
{
	char	**temp;

	temp = malloc(sizeof(char) * ft_strlenn(env));
	
	return (temp);
}

void	show_sort_env(char **env)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_sort_env(env);
	while (temp[i])
	{
		printf("%s\n", temp[i]);
		i++;
	}
	free(temp);
}

int	main(int ac, char **av, char **envp)
{
	if (ac == 1)
		show_sort_env(envp);
	else if (ac > 2)
		return (0);
	(void)av;
}
