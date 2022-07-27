/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:10:17 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/27 14:46:19 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../srcs/minishell.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*counter;

	if (!lst)
		return (0);
	count = 1;
	counter = lst->next;
	while (counter != NULL)
	{
		count++;
		counter = counter->next;
	}
	return (count);
}

int	ft_lstsiize(t_list *lst)
{
	int		count;
	t_list	*counter;

	if (!lst)
		return (0);
	count = 1;
	counter = lst->next;
	while (counter != NULL)
	{
		printf("%s\n", ((t_env *)(counter->content))->variable);
		count++;
		counter = counter->next;
	}
	return (count);
}
