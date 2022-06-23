#include "minishell.h"

// void	expand_variable(char *str, t_list *env)
// {

// }

// void	expansion(t_list **lexer_list, t_list *env)
// {
// 	t_list	*tmp;
// 	t_lexer	*caster;
// 	char	*expanded;

// 	tmp = (*lexer_list);
// 	caster = NULL;
// 	expanded = NULL;
// 	while (tmp)
// 	{
// 		caster = (t_lexer *)(tmp->content);
// 		if (caster->token == TOKEN_DQUOTE || caster->token == TOKEN_DOLLAR)
// 		{
// 			expanded = expand_variable(caster->text, env);
// 		}
// 		tmp = tmp->next;
// 	}

// }

void	ft_parser(t_list **lexer_list)
{
	
}
