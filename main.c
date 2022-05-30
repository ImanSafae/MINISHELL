/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:12 by itaouil           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/30 14:17:54 by itaouil          ###   ########.fr       */
=======
/*   Updated: 2022/05/30 16:04:01 by anggonza         ###   ########.fr       */
>>>>>>> 6a20befa22fdd42e005a0d4493f71ee2ab717e6b
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	(void)argc;
	(void)argv;

	env = create_env(envp);
<<<<<<< HEAD
	// ft_export(&env, NULL);
	ft_env(&env);
	system("leaks a.out");
=======
	ft_export(&env, NULL, NULL);
	// ft_env(&env);
	// free_list(&env);
	//ft_free_list(&env);
	//print_env(env);
	//system("leaks a.out");
>>>>>>> 6a20befa22fdd42e005a0d4493f71ee2ab717e6b
}
