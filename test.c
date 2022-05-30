/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:08 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/30 15:28:45 by anggonza         ###   ########.fr       */
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
