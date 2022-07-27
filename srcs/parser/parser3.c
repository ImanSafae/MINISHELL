/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:36:03 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/27 11:10:17 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	at_least_one_command(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;

	tmp = (*lexer_list);
	caster = NULL;
	while (tmp)
	{
		caster = (t_lexer *)(tmp->content);
		if (caster->token != TOKEN_INFILE && caster->token != TOKEN_OUTFILE
			&& caster->token != TOKEN_HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	incr_split_list_pipes(t_lexer **caster, t_list **tmp, t_cmd **c, int *i)
{
	*caster = (t_lexer *)((*tmp)->content);
	if ((*caster)->token == TOKEN_PIPE)
	{
		*tmp = (*tmp)->next;
		if (!*tmp)
		{
			send_error(PARSING, UNEXPECTEDTOK, "|");
			return (0);
		}
		get_command(tmp, &((*c)[*i]));
		if (*tmp)
			(*c)[*i].args = get_args(tmp, &((*c)[*i]));
		(*i)++;
	}
	else
			*tmp = (*tmp)->next;
	return (1);
}

void	check_error_outfile(t_lexer *c)
{
	if (c->token == TOKEN_INFILE && access(c->text, F_OK) == -1)
		send_error(PARSING, WRONG_FILE, c->text);
}
