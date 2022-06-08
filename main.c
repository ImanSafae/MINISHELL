/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:12 by itaouil           #+#    #+#             */
/*   Updated: 2022/06/08 18:32:34 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	(void)argc;
	(void)argv;
	char	*str;
	
	env = create_env(envp);
	//ft_export(&env, "VARTEST", NULL);
	//ft_export(&env, NULL, NULL);
	//ft_env(&env);
	while (1)
	{
		str = readline("minishell obama is listening>");
	}
	free(str);
	free_list(&env);
	system("leaks minishell");
}
