/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:12 by itaouil           #+#    #+#             */
/*   Updated: 2022/06/27 12:43:24 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*str;

	(void)argc;
	(void)argv;
	env = create_env(envp);
	detect_signals();
	while (1)
	{
		str = readline("minishell obama is listening > ");
		if (!ft_strncmp(str, "exit", 4))
			break ;
		if (ft_strlen(str) == 0)
			continue ;
		ft_lexer(str, &env);
		free(str);
	}
	free_env(&env);
	system("leaks minishell");
}

// COMMENTAIRE D'AU DESSUS
// ft_export(&env, "VARTEST", "lol");
	// ft_export(&env, NULL, NULL);
	//ft_unset("PATH=", &env);
	// ft_env(&env);
