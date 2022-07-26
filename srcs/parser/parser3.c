/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:36:03 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/26 15:37:47 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	at_least_one_command(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;

	tmp = (*lexer_list);
	caster = NULL;
	while (tmp)
	{
		caster = (t_lexer *)(tmp->content);
		if (caster->token != TOKEN_INFILE && caster->token != TOKEN_OUTFILE
			&& caster->token != TOKEN_HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
