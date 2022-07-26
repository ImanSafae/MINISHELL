/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:33:29 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/26 16:03:42 by itaouil          ###   ########.fr       */
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
	if (token == TOKEN_INFILE)
		command->infile = ft_strdup(file);
	if (token == TOKEN_APPEND)
	{
		command->append = 1;
		command->outfile = ft_strdup(file);
	}
	else if (token == TOKEN_OUTFILE)
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

int	count_args(t_list *pointer)
{
	t_lexer	*caster;
	t_list	*tmp;
	int		count;

	tmp = pointer;
	count = 0;
	caster = (t_lexer *)(tmp->content);
	while (tmp && caster && caster->token != TOKEN_PIPE)
	{
		caster = (t_lexer *)(tmp->content);
		if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
			|| caster ->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**get_args(t_list **pointer, t_cmd *cmd)
{
	int		tab_size;
	char	**args;
	int		i;
	t_lexer	*caster;

	tab_size = count_args(*pointer);
	args = malloc(sizeof(char *) * (tab_size + 1));
	i = 0;
	caster = NULL;
	while ((*pointer)
		&& ((t_lexer *)((*pointer)->content))->token != TOKEN_PIPE)
	{
		caster = (t_lexer *)((*pointer)->content);
		if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
			|| caster ->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
		{
			args[i] = ft_strdup(caster->text);
			i++;
		}
		else if (caster->token == TOKEN_APPEND || caster->token == TOKEN_HEREDOC
			|| caster->token == TOKEN_INFILE || caster->token == TOKEN_OUTFILE)
			parse_redirections(caster->token, cmd, caster->text);
		(*pointer) = (*pointer)->next;
	}
	args[tab_size] = 0;
	return (args);
}
