/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:29:06 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/06 16:49:12 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*retrieve_variable(char *line, int *i, int single_quoted)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	ret = ft_chardup(line[*i]);
	(*i)++;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_')
		&& !ft_isspace(line[*i]))
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		(*i)++;
	}
	if (!single_quoted)
		expand_variable(&ret);
	return (ret);
}

char	*retrieve_squoted_text(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	ret = NULL;
	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	if (line[*i] && line[*i] != '\'')
	{
		ret = ft_chardup(line[*i]);
		(*i)++;
	}
	while (line[*i] && line[*i] != '\'')
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		(*i)++;
	}
	if (!line[*i])
	{
		send_error(PARSING, OPEN_QUOTE, line);
		ret = ERROR_CHAR;
	}
	return (ret);
}

char	*retrieve_dquoted_text(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	char	*line_tmp;
	int		i_tmp;

	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	i_tmp = *i;
	tmp = ft_strndup(line, 0, i_tmp - 1);
	line_tmp = ft_strjoin(tmp, check_for_envvar(&(line[i_tmp])));
	free(tmp);
	if (line_tmp[i_tmp])
		ret = ft_chardup(line_tmp[i_tmp]);
	i_tmp++;
	get_index(line, i, TOKEN_DQUOTE);
	while (line_tmp[i_tmp] && line_tmp[i_tmp] != '\"')
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line_tmp[i_tmp]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		i_tmp++;
		free(tmp);
		free(tmp2);
	}
	if (!line_tmp[i_tmp])
		send_error(PARSING, OPEN_QUOTE, line);
	free(line_tmp);
	return (ret);
}

char	*retrieve_text(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	int		i_tmp;

	ret = ft_chardup(line[*i]);
	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	while (line[*i] && ft_isnotspecial(line[*i]) && !ft_isspace(line[*i]))
	{
		i_tmp = *i;
		if (line[*i] == '$')
		{
			tmp2 = retrieve_variable(line, &i_tmp, 0);
			get_index(line, i, TOKEN_DOLLAR);
		}
		else if (line[*i] == '\"')
			tmp2 = retrieve_dquoted_text(line, i);
		else if (line[*i] == '\'')
			tmp2 = retrieve_squoted_text(line, i);
		else
			tmp2 = ft_chardup(line[*i]);
		tmp = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		if (ft_strlen(line) > *i)
			(*i)++;
	}
	return (ret);
}

char	*retrieve_heredoc(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	int		into_quote;

	(*i) += 2;
	into_quote = 0;
	while (ft_isspace(line[*i]))
		(*i)++;
	into_quote = 0;
	if (line[*i] == '\"' || line[*i] == '\'')
	{
		into_quote = 1;
		(*i)++;
	}
	ret = ft_chardup(line[*i]);
	(*i)++;
	while (line[*i] && ft_isnotspecial(line[*i])
		&& (!ft_isspace(line[*i] || (ft_isspace && into_quote == 1))))
	{
		if (line[*i] == '\"' || line[*i] == '\'')
		{
			if (ft_strlen(line) > i)
				(*i)++;
			else
			{
				(*i)++;
				break ;
			}
			into_quote = 1;
		}
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		(*i)++;
	}
	return (ret);
}
