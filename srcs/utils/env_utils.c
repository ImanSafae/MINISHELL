/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:23:01 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/12 22:20:59 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_list *env, char *variable)
{
	t_env	*caster;
	size_t	len;
	char	*ret;

	caster = NULL;
	len = ft_strlen(variable);
	ret = NULL;
	while (env)
	{
		caster = (t_env *)(env->content);
		if (!ft_strncmp(variable, caster->variable, len)
			&& ft_strlen(caster->variable) == len)
		{
			ret = caster->value;
			break ;
		}
		env = env->next;
	}
	return (ret);
}

void	delete_element_from_list(t_list **previous, t_list **to_delete, t_env **line)
{
	t_env	*caster;

	caster = (t_env *)((*to_delete)->content);
	(*line) = new_env_entry(caster->variable, caster->value);
	(*previous)->next = (*to_delete)->next;
	ft_lstdelone((*to_delete), empty_env_element);
}

t_env	*duplicate_env_line(t_env *line)
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
		ft_lstadd_back(&dup, ft_lstnew(duplicate_env_line(tmp->content)));
		tmp = tmp->next;
	}
	return (dup);
}
