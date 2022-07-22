/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:31:14 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/22 12:39:07 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser_check_caster_token(t_lexer *caster)
{
	if (caster->token == TOKEN_OUTFILE && access(caster->text, F_OK) == -1)
		touch_outfile(caster->text);
	if (caster->token == TOKEN_INFILE && access(caster->text, F_OK) == -1)
		send_error(PARSING, WRONG_FILE, caster->text);
}

void	assign_t_cmd(t_cmd **cmd, int nb_of_cmds)
{
	int	i;

	i = 0;
	while (i < nb_of_cmds)
	{
		(*cmd)[i].command = NULL;
		(*cmd)[i].args = NULL;
		(*cmd)[i].infile = NULL;
		(*cmd)[i].outfile = NULL;
		(*cmd)[i].hd_delimiter = NULL;
		i++;
	}
}

void	split_list_on_pipes(t_list **lexer_list, t_cmd **command)
{
	t_list	*tmp;
	t_lexer	*caster;
	int		i;

	tmp = (*lexer_list);
	caster = (t_lexer *)(tmp->content);
	i = 1;
	if (tmp && ((t_lexer *)(tmp->content))->token != TOKEN_SPACE)
		(*command)[0].args = get_args(&tmp, &((*command)[0]));
	while (tmp)
	{
		caster = (t_lexer *)(tmp->content);
		if (caster->token == TOKEN_PIPE)
		{
			tmp = tmp->next;
			if (!tmp)
			{
				send_error(PARSING, UNEXPECTEDTOK, "|");
				return ;
			}
			get_command(&tmp, &((*command)[i]));
			if (tmp)
				(*command)[i].args = get_args(&tmp, &((*command)[i]));
			i++;
		}
		else
			tmp = tmp->next;
	}
}
