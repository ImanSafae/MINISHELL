/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:12 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/30 18:04:14 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	(void)argc;
	(void)argv;

	env = create_env(envp);
	ft_export(&env, NULL, NULL);
	// ft_env(&env);
	free_list(&env);
	system("leaks a.out");
}
