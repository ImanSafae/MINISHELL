#include "minishell.h"

void	expansion(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;

	tmp = (*lexer_list);
	caster = NULL;
	while (tmp)
	{
		caster = (t_lexer *)(tmp->content);
		if (caster->token == TOKEN_DQUOTE || caster->token == TOKEN_DOLLAR)
		tmp = tmp->next;
	}
}

void	ft_parser(t_list **lexer_list)
{

}
