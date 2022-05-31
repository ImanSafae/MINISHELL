/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:24:41 by anggonza          #+#    #+#             */
/*   Updated: 2022/05/30 17:55:30 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	empty_env_element(void *element)
{
	t_env	*_element;

	_element = (t_env *)element;
	free(_element->variable);
	free(_element->value);
	free(_element);
}

void	free_list(t_list **list)
{
	ft_lstclear(list, &empty_env_element);
}

void	ft_free_list(t_list **liste)
{
	t_list	*temp;

	while(*liste)
	{
		temp = *liste;
		*liste = (*liste)->next;
		free(temp);
	}
	liste = NULL;
}
