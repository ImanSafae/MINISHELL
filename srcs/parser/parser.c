/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:40:24 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/22 12:38:08 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_command(t_list **pointer, t_cmd *cmd)
{
	t_lexer	*caster;

	caster = (t_lexer *)((*pointer)->content);
	while ((*pointer) && caster->token == TOKEN_SPACE)
	{
		(*pointer) = (*pointer)->next;
		if (*pointer)
			caster = (t_lexer *)((*pointer)->content);
	}
	if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
		|| caster->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
	{
		cmd->command = ft_strdup(caster->text);
		(*pointer) = (*pointer)->next;
	}
	if (*pointer)
		caster = (t_lexer *)((*pointer)->content);
	while ((*pointer) && caster->token == TOKEN_SPACE)
	{
		(*pointer) = (*pointer)->next;
		if (*pointer)
			caster = (t_lexer *)((*pointer)->content);
	}
}

void	main_parser(t_list **lexer_list)
{
	int		nb_of_pipes;
	t_exec	*exec;
	t_cmd	*cmd;

	nb_of_pipes = count_pipes(*lexer_list);
	exec = malloc(sizeof(t_exec));
	cmd = malloc(sizeof(t_cmd) * (nb_of_pipes + 1));
	assign_t_cmd(&cmd, nb_of_pipes + 1);
	if (((t_lexer *)((*lexer_list)->content))->token == TOKEN_PIPE)
	{
		send_error(PARSING, UNEXPECTEDTOK, "|");
		return ;
	}
	split_list_on_pipes(lexer_list, &cmd);
	if (!cmd)
		return ;
	exec->commands = cmd;
	exec->pipes = nb_of_pipes;
	ft_exec(exec);
	free_exec_structs(&exec);
}

static int	at_least_one_command(t_list **lexer_list)
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

void	ft_parser(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;

	tmp = (*lexer_list);
	caster = NULL;
	if (at_least_one_command(lexer_list))
	{
		main_parser(lexer_list);
	}
	else
	{
		caster = (t_lexer *)(tmp->content);
		while (tmp)
		{
			parser_check_caster_token(caster);
			if (caster->token == TOKEN_HEREDOC)
			{
				heredoc(caster->text);
				unlink("/tmp/heredoc.tmp");
				close(g_all.fd_to_close);
			}
			tmp = tmp->next;
		}
	}
}
