/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:12 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/27 20:05:29 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	t_env	*first;
	t_list	*sorted;

	env = create_env(envp);
	sorted = recreate_sorted_env(envp);
	// printf("SORTED:\n");
	// print_env(sorted);
	// printf("NORMAL:\n");
	// print_env(env);
	// first = first_in_ascii(&env);
	// printf("first in ascii is %s\n", first->variable);
	}
