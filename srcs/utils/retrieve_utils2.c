/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:14:52 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/07 17:20:28 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	squote_utils(char *line, int *i, char **ret)
{
	if (ft_strlen(&(line[*i])) > 1)
		(*i)++;
	else
		return (1);
	if (line[*i] && line[*i] != '\'')
	{
		*ret = ft_chardup(line[*i]);
		(*i)++;
	}
	return (0);
}

void	check_unclose_squoted(char *line, char **ret, int *i)
{
	if (!line[*i])
	{
		free(*ret);
		send_error(PARSING, OPEN_QUOTE, line);
		*ret = ft_strdup("error");
	}
	else
		(*i)++;
}
