/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:30:31 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/16 18:27:27 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable(char **value)
{
	t_list	*tmp;

	tmp = g_all.env;
	if (!ft_strncmp(*value, "?", 1) && ft_strlen(*value) == 1)
	{
		free(*value);
		*value = ft_itoa(g_all.exit_code);
		return ;
	}
	while (tmp->next)
	{
		if (ft_strlen(*value) == ft_strlen(((t_env *)(tmp->content))->variable))
		{
			if (!ft_strncmp(*value, ((t_env *)(tmp->content))->variable,
				ft_strlen(*value)))
			{
				free(*value);
				*value = ft_strdup(((t_env *)(tmp->content))->value);
				return ;
			}
		}
		tmp = tmp->next;
	}
}

void	join_quotes_and_text(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;
	t_list	*to_delete;
	char	*joined_text;

	tmp = (*lexer_list);
	caster = NULL;
	while (tmp)
	{
		caster = (t_lexer *)(tmp->content);
		if (tmp && tmp->next)
		{
			if ((caster->token == TOKEN_TEXT && ((t_lexer *)(tmp->next->content))->token == TOKEN_DQUOTE)
				|| (caster->token == TOKEN_DQUOTE && ((t_lexer *)(tmp->next->content))->token == TOKEN_TEXT))
			{
				joined_text = ft_strjoin(caster->text, ((t_lexer *)(tmp->next->content))->text);
				free(caster->text);
				caster->text = ft_strdup(joined_text);
				free(joined_text);
				to_delete = tmp->next;
				tmp->next = tmp->next->next;
				ft_lstdelone(to_delete, empty_lexer_element);
				tmp = tmp->next;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
}
