/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:11:20 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/07 16:31:43 by anggonza         ###   ########.fr       */
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
