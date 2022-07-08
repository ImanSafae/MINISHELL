/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:55:10 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/08 14:24:56 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_quote(char *line, int type)
{
	char	research;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (type == TOKEN_DQUOTE)
		research = '\"';
	else
		research = '\'';
	while (line[i])
	{
		if (line[i] == research)
			count++;
		i++;
	}
	return (count);
}

int	nothing_after_redirect(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<') && (int)ft_strlen(line) - i <= 1)
			return (1);
		else if ((!ft_strncmp(line, ">>", 2) || !ft_strncmp(line, "<<", 2))
			&& !line[i + 2])
			return (1);
		i++;
	}
	return (0);
}

int	check_error(char *line, int error)
{
	if (error)
		return (1);
	if (count_quote(line, TOKEN_DQUOTE) % 2 == 1
		|| count_quote(line, TOKEN_SQUOTE) % 2 == 1)
	{
		send_error(PARSING, OPEN_QUOTE, line);
		return (1);
	}
	if (nothing_after_redirect(line))
	{
		send_error(PARSING, OPEN_REDIRECTION, line);
		return (1);
	}
	return (0);
}

char	*get_next_word(char *str, int *index)
{
	char	*ret;
	char	*tmp;
	char	*buffer;

	ret = NULL;
	tmp = NULL;
	buffer = NULL;
	if (!str)
		return (NULL);
	if (str[*index])
		ret = ft_chardup(str[*index]);
	(*index)++;
	while (str[*index] && !ft_isspace(str[*index])
		&& ft_isnotspecial(str[*index]))
	{
		tmp = ft_strdup(ret);
		free(ret);
		buffer = ft_chardup(str[*index]);
		ret = ft_strjoin(tmp, buffer);
		free(buffer);
		free(tmp);
		(*index)++;
	}
	return (ret);
}
