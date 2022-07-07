/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:11:20 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/07 17:18:02 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_heredoc(char *line, int *i, int *into_quote)
{
	(*i) += 2;
	while (ft_isspace(line[*i]))
		(*i)++;
	*into_quote = 0;
	if (line[*i] == '\"' || line[*i] == '\'')
	{
		*into_quote = 1;
		(*i)++;
	}
	(*i)++;
}

int	heredoc_quoted(char *line, int *i, int *into_quote)
{
	if (line[*i] == '\"' || line[*i] == '\'')
	{
		if ((int)ft_strlen(line) - 1 > *i)
			(*i)++;
		else
		{
			(*i)++;
			return (0);
		}
		*into_quote = 1;
	}
	return (1);
}

void	determine_tmp2_value(char *line, int *i, char **tmp2)
{
	int	i_tmp;

	i_tmp = *i;
	if (line[*i] == '$')
	{
		*tmp2 = retrieve_variable(line, &i_tmp, 0);
		get_index(line, i, TOKEN_DOLLAR);
	}
	else if (line[*i] == '\"')
		*tmp2 = retrieve_dquoted_text(line, i);
	else if (line[*i] == '\'')
		*tmp2 = retrieve_squoted_text(line, i);
	else
		*tmp2 = ft_chardup(line[*i]);
}

char	*dquoted_utils(char *line, int *i, int *i_tmp, char **tmp)
{
	char	*line_tmp;

	line_tmp = NULL;
	(*i)++;
	*i_tmp = *i;
	*tmp = ft_strndup(line, 0, *i_tmp - 1);
	line_tmp = ft_strjoin(*tmp, check_for_envvar(&(line[*i_tmp])));
	free(*tmp);
	(*i_tmp)++;
	get_index(line, i, TOKEN_DQUOTE);
	return (line_tmp);
}

void	check_unclose_dquoted(char *line_tmp, int i_tmp, char **ret, int *i)
{
	if (!line_tmp[i_tmp])
	{
		free(*ret);
		send_error(PARSING, OPEN_QUOTE, line_tmp);
		*ret = ft_strdup("error");
	}
	else
		(*i)++;
}
