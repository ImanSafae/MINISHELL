/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:23 by itaouil           #+#    #+#             */
/*   Updated: 2022/06/13 20:17:33 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_element_from_list(t_list **previous, t_list **to_delete)
{
	(*previous)->next = (*to_delete)->next;
	ft_lstdelone((*to_delete), delete_element);
}

t_env	*duplicate_line(t_env *line)
{
	t_env	*duplicate;

	duplicate = malloc(sizeof(t_env));
	duplicate->variable = ft_strdup(line->variable);
	if (line->value)
		duplicate->value = ft_strdup(line->value);
	return (duplicate);
}

t_list	*duplicate_list(t_list *list)
{
	t_list	*dup;
	t_list	*tmp;

	dup = NULL;
	tmp = list;
	while (tmp)
	{
		ft_lstadd_back(&dup, ft_lstnew(duplicate_line(tmp->content)));
		tmp = tmp->next;
	}
	return (dup);
}

char	*ft_strndup(char *str, int begin, int end)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (end - begin + 2));
	i = 0;
	while (ret[i])
	{
		ret[i] = str[begin];
		i++;
		begin++;
	}
	return (ret);
}