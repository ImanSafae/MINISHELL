#include "minishell.h"

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
		if (caster->token == TOKEN_TEXT)
		{
			uncapitalized = uncapitalize_str(caster->text);
			free(caster->text);
			caster->text = uncapitalized;
			break ;
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
