/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:08 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/02 20:17:43 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->next)
	{
		printf("%s=%s\n", (((t_env *)(tmp->content))->variable),
			(((t_env *)(tmp->content))->value));
		tmp = tmp->next;
	}
}

void	print_lexer_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s\n", ((t_lexer *)(tmp->content))->text);
		tmp = tmp->next;
		printf("next\n");
	}
}

void	print_commands_tab(t_cmd *commands, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < (nb_of_pipes + 1))
	{
		printf("command = %s\n", (commands[i]).command);
		printf("args = %s\n", (commands[i]).args);
		i++;
	}
}
