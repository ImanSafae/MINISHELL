/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:24:41 by anggonza          #+#    #+#             */
/*   Updated: 2022/05/30 15:24:42 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list **list)
{
	ft_lstclear(list, &delete_element);
}

// void	ft_free_list(t_list **liste)
// {
// 	t_list	*temp;

// 	while(*liste)
// 	{
// 		temp = *liste;
// 		*liste = (*liste)->next;
// 		free(temp);
// 	}
// 	liste = NULL;
// }
