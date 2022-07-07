/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:09:00 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/07 20:51:43 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnotspecial(char c)
{
	if (c == '>' || c == '<' || c == '|')
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

void	check_sometoken(char *line, int token, char **content, int *i)
{
	if (token == TOKEN_TEXT)
		*content = retrieve_text(&(*line), i);
	else if (token == TOKEN_DQUOTE)
		*content = retrieve_dquoted_text(line, i);
	else if (token == TOKEN_PIPE)
	{
		*content = ft_chardup(line[*i]);
		(*i)++;
	}
	else if (token == TOKEN_HEREDOC)
		*content = retrieve_heredoc(line, i);
}

int	check_error_or_update(char *content, t_list **list, int token)
{
	if (!ft_strncmp(content, ERROR_CHAR, ft_strlen("error")))
		return (0);
	if (content)
		update_lexer_list(list, content, token);
	return (1);
}

void	all_check_errors(char *line, int *error)
{
	*error = 1;
	if (ft_strlen(line) == 1)
	{
		if (*line == '\'' || *line == '\"')
			send_error(PARSING, OPEN_QUOTE, line);
		else if (*line == '<' || *line == '>')
			send_error(PARSING, OPEN_REDIRECTION, line);
		else
			*error = 0;
	}
	if (ft_strlen(line) == 2)
	{
		if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2))
			send_error(PARSING, OPEN_REDIRECTION, line);
		else if (!ft_strncmp(line, "\"\"", 2) || !ft_strncmp(line, "\'\'", 2))
			send_error(PARSING, UNKNOWN_COMMAND, "");
		else
			*error = 0;
	}
}
