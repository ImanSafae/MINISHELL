#include "../minishell.h"

void	uncapitalize_cmd(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;
	char	*uncapitalized;

	tmp = (*lexer_list);
	caster = NULL;
	uncapitalized = NULL;
	while (tmp)
	{
		caster = (t_lexer *)(tmp->content);
		if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
			|| caster->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
		{
			if (caster->text)
			{
				uncapitalized = uncapitalize_str(caster->text);
				free(caster->text);
				caster->text = ft_strdup(uncapitalized);
				free(uncapitalized);
			}
		}
		tmp = tmp->next;
	}
}

// void	ft_parser(t_list **lexer_list)
// {
// 	/* Créer une struct qui va résumer ce qu'il faut exec */
// 	t_exec	*exec;
// 	t_cmd	*cmds;

// 	exec = malloc(sizeof(t_exec));
// 	exec->pipes = count_pipes(*lexer_list);
// 	uncapitalize_cmd(lexer_list);

// 	/* free la lexer_list avant la fin de cette fonction */
// }
