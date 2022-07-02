/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:28:01 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/02 21:38:09 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnotspecial(char c)
{
	if (c == '\'' || c == '\"' || c == '>' || c == '<' || c == '$' || c == '|')
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

char	*ft_chardup(char c)
{
	char	*ret;

	ret = malloc(sizeof(char) * 2);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}
