/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:23 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/30 18:29:44 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_element_from_list(t_list **previous, t_list **to_delete)
{
	(*previous)->next = (*to_delete)->next;
	//ft_lstdelone((*to_delete), delete_element);
}

t_list	*duplicate_list(t_list *list)
{
	int		size;
	t_list	*dup;
	t_list	*tmp;

	size = ft_lstsize(list);
	dup = NULL;
	tmp = list;
	while (tmp)
	{
		ft_lstadd_back(&dup, ft_lstnew(tmp->content));
		tmp = tmp->next;
	}
	return (dup);
}
