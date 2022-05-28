/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:23 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/28 19:13:24 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_element_from_list(t_list **previous, t_list **to_delete)
{
	(*previous)->next = (*to_delete)->next;
	ft_lstdelone((*to_delete), delete_element);
}
