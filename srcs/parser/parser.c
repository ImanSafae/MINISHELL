/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:40:24 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/26 15:36:16 by itaouil          ###   ########.fr       */
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
	get_command(&tmp, &((*command)[0]));
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

void	ft_parser(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;

	tmp = (*lexer_list);
	caster = NULL;
	if (at_least_one_command(lexer_list))
		main_parser(lexer_list);
	else
	{
		caster = (t_lexer *)(tmp->content);
		while (tmp)
		{
			if (caster->token == TOKEN_OUTFILE
				&& access(caster->text, F_OK) == -1)
				touch_outfile(caster->text);
			if (caster->token == TOKEN_INFILE
				&& access(caster->text, F_OK) == -1)
				send_error(PARSING, WRONG_FILE, caster->text);
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
