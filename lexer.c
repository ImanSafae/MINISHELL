/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:18:18 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/06 19:19:14 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '"')
		return (2);
	else if (c == '|')
		return (3);
	else if (c == 103) // c'est le guillemet simple
	{
		return (4);
	}
	else if (c == '>' || c == '<')
	{
		return (5);
	}
	else if (c == '$')
	{
		return (6);
	}
	return (0);
	// TODO TYPE A RAJOUTER SI OUBLI CHAQUE TYPE = UN INT
}

t_token	*add_token_to_list(char c, int type)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token));
	ret->c = c;
	ret->type = type;
	return (ret);
}

t_list	*each_char_token(char *line)
{
	int		i;
	t_list	*chars;

	i = 1;
	chars = ft_lstnew(add_token_to_list(line[0], get_type(line[0])));
	while (line[i])
	{
		if (line[i] != ' ')
			ft_lstadd_back(&chars, ft_lstnew(add_token_to_list(line[i],
						get_type(line[i]))));
		i++;
	}
	return (chars);
}

int	get_size(t_list *chars)
{
	t_list	*tmp;
	int		size_tab;
	int		actual_type;
	t_token	*tmp_tok;

	tmp = chars;
	while (tmp)
	{
		tmp_tok = (t_token *)tmp->content;
		if (tmp_tok->type != actual_type)
		{
			size_tab++;
			actual_type = tmp_tok->type;
		}
		tmp = tmp->next;
	}
	return (size_tab);
}


// PAS ENCORE FINI
char	**tokenisation(t_list *chars)
{
	t_token	*tmp;
	char	**tokens;
	int		actual_type;
	int		depart_str;
	int		fin_str; // indice du debut et fin de mot

	tokens = malloc(get_size(chars));
	tmp = (t_token *)chars->content;
	actual_type = tmp->type;
	depart_str = 0;
	fin_str = 0;
	while (chars)
	{
		while (actual_type == tmp->type)
		{
			chars = chars->next;
			tmp = (t_token *)chars->content;
		}
		chars = chars->next;
	}
}
