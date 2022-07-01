/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:23 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/01 18:18:26 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_element_from_list(t_list **previous, t_list **to_delete)
{
	(*previous)->next = (*to_delete)->next;
	ft_lstdelone((*to_delete), delete_element);
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
/*
char	*ft_strndup(char *str, int begin, int end)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (end - begin + 2));
	i = 0;
	while (begin <= end)
	{
		ret[i] = str[begin];
		i++;
		begin++;
	}
	ret[i] = '\0';
	return (ret);
}
*/
int	ft_isnotspecial(char c)
{
	if (c == '\'' || c == '\"' || c == '>' || c == '<' || c == '$' || c == '|')
		return (0);
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

char	*ft_chardup(char c)
{
	char	*ret;

	ret = malloc(sizeof(char) * 2);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

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
		if (!ft_strncmp(variable, caster->variable, len) && ft_strlen(caster->variable) == len)
		{
			ret = caster->value;
			break ;
		}
		env = env->next;
	}
	return (ret);
}

char	*uncapitalize_str(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			ret[i] = (str[i] + 32);
		else
			ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strndup(char *str, int start, int end)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (end - start + 1));
	i = start;
	if (!ret)
		return (NULL);
	while (str[i] && i <= end)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin_with_space(char *s1, char *s2)
{
	size_t	total_length;
	char	*ret;
	int		i;

	// if (!s1 || !s2)
	// 	return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	total_length = ft_strlen(s1) + ft_strlen(s2) + 2;
	ret = malloc(sizeof(char) * total_length);
	i = 0;
	while(s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = ' ';
	i = 0;
	while (s2[i])
	{
		ret[i] = s2[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
