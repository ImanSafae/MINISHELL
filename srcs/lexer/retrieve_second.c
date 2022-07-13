/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_second.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:03:37 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/12 16:04:23 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*retrieve_filename(char *line, int *i)
{
	char	*ret;

	ret = NULL;
	(*i)++;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i])
		ret = get_next_word(line, i);
	return (ret);
}

char	*retrieve_pipe(char *line, int *i)
{
	
}
