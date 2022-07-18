/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:40:24 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/18 14:33:52 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(t_list *list)
{
	t_list	*tmp;
	t_lexer	*caster;
	int		count;

	tmp = list;
	caster = NULL;
	count = 0;
	while (tmp)
	{
		caster = (t_lexer *)tmp->content;
		if (caster->token == TOKEN_PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	parse_redirections(int token, t_cmd *command, char *file)
{
	if (token == TOKEN_APPEND)
	{
		command->append = 1;
		command->outfile = ft_strdup(file);
	}
	if (token == TOKEN_INFILE)
		command->infile = ft_strdup(file);
	if (token == TOKEN_OUTFILE)
		command->outfile = ft_strdup(file);
	if (token == TOKEN_HEREDOC)
		command->hd_delimiter = ft_strdup(file);
}

void	add_text_to_string(char **str, char *to_append)
{
	char	*tmp;

	if (*str)
	{
		tmp = ft_strdup(*str);
		free(*str);
		(*str) = ft_strjoin_with_space(tmp, to_append);
		free(tmp);
	}
	else
		(*str) = ft_strdup(to_append);
}

char	*get_command(t_list **pointer, t_cmd *cmd)
{
	char	*ret;
	t_lexer	*caster;

	caster = (t_lexer *)((*pointer)->content);
	ret = NULL;
	if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
		|| caster->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
	{
		ret = ft_strdup(caster->text);
		(*pointer) = (*pointer)->next;
		// if (*pointer)
			// caster = (t_lexer *)((*pointer)->content);
	}
	while ((*pointer) && ((t_lexer *)((*pointer)->content))->token != TOKEN_PIPE)
	{
		caster = (t_lexer *)((*pointer)->content);
		if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
			|| caster ->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
			add_text_to_string(&ret, caster->text);
		else if (caster->token == TOKEN_APPEND || caster->token == TOKEN_HEREDOC
			|| caster->token == TOKEN_INFILE || caster->token == TOKEN_OUTFILE)
			parse_redirections(caster->token, cmd, caster->text);
		(*pointer) = (*pointer)->next;
		// if (*pointer)
	}
	return (ret);
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

void	split_list_on_pipes(t_list **lexer_list, int nb_of_cmds, t_cmd **command)
{
	t_list	*tmp;
	t_lexer	*caster;
	int		i;

	tmp = (*lexer_list);
	caster = (t_lexer *)(tmp->content);
	i = 1;
	(*command)[0].command = get_command(&tmp, &((*command)[0]));
	while (tmp && (i < nb_of_cmds))
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
			((*command)[i]).command = get_command(&tmp, &((*command)[i]));
			i++;
		}
		else
			tmp = tmp->next;
	}
}

void	separate_cmd_from_args(t_cmd **cmds, int nb_of_cmds)
{
	int		i;
	int		j;
	char	*tmp_command;
	char	*tmp_args;

	i = 0;
	j = 0;
	tmp_command = NULL;
	tmp_args = NULL;
	if (!((*cmds)[i].command))
		return ;
	while (i < (nb_of_cmds) && ((*cmds)[i].command))
	{
		while (((*cmds)[i].command)[j] && !ft_isspace(((*cmds)[i].command)[j]))
			j++;
		tmp_command = ft_strndup((*cmds)[i].command, 0, j - 1);
		if (((*cmds)[i].command)[j])
			tmp_args = ft_strndup((*cmds)[i].command, j + 1, ft_strlen((*cmds)[i].command));
		free((*cmds)[i].command);
		(*cmds)[i].command = ft_strdup(tmp_command);
		free(tmp_command);
		(*cmds)[i].args = ft_split(tmp_args, ' ');
		free(tmp_args);
		tmp_args = NULL;
		i++;
		j = 0;
	}
}

void	main_parser(t_list **lexer_list) // IL FAUT ENCORE GERER LE HEREDOC + CORRIGER LE LEXING DE APPEND POUR QU'IL RECUPERE L'OUTFILE AU LIEU DE JUSTE ">>"
{
	int		nb_of_pipes;
	t_exec	*exec;
	t_cmd	*cmd; // c'est un tableau de structures et non pas une liste chaînée

	nb_of_pipes = count_pipes(*lexer_list);
	exec = malloc(sizeof(t_exec));
	cmd = malloc(sizeof(t_cmd) * (nb_of_pipes + 1));
	assign_t_cmd(&cmd, nb_of_pipes + 1);
	if (((t_lexer *)((*lexer_list)->content))->token == TOKEN_PIPE)
	{
		send_error(PARSING, UNEXPECTEDTOK, "|");
		return ;
	}
	split_list_on_pipes(lexer_list, nb_of_pipes + 1, &cmd);
	if (!cmd)
		return ;
	exec->commands = cmd;
	exec->pipes = nb_of_pipes;
	separate_cmd_from_args(&cmd, nb_of_pipes + 1);
	// print_commands_tab(cmd, nb_of_pipes);
	ft_exec(exec);
	//free_exec_structs(&exec);
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
		main_parser(lexer_list);
	else
	{
		caster = (t_lexer *)(tmp->content);
		while (tmp)
		{
			if (caster->token == TOKEN_OUTFILE && access(caster->text, F_OK) == -1)
				touch_outfile(caster->text);
			if (caster->token == TOKEN_INFILE && access(caster->text, F_OK) == -1)
				send_error(PARSING, WRONG_FILE, caster->text);
			if (caster->token == TOKEN_HEREDOC)
			{
				heredoc(caster->text);
				close(g_all.fd_to_close);
			}
			tmp = tmp->next;
		}
	}
}
