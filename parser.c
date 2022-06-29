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

t_cmd	*split_commands(t_list **lexer_list)
{
	/* Séparer chaque "bloc" entre les pipes, c'est-à-dire une commande + ses args + éventuellement un infile/un outfile
	Chaque bloc doit être mis dans un maillon de liste chaînée t_cmd : un maillon = un bloc de commande = une commande + ses args/flags
	S'il n'y a pas de pipe, la liste chaînée n'a qu'un seul maillon
	
	Le premier élément avec un token text/quote/dollar doit correspondre à la commande, ceux qui viennent après sont des args */

	t_list	*tmp;
	t_cmd	*cmds;
	char	*command;
	char	*args;

	tmp = (*lexer_list);
	cmds = NULL;
	while (tmp)
	{

		tmp = tmp->next;
	}
}

void	ft_parser(t_list **lexer_list)
{
	/* Créer une struct qui va résumer ce qu'il faut exec */
	t_exec	*exec;
	t_cmd	*cmds;

	exec = malloc(sizeof(t_exec));
	exec->pipes = count_pipes(*lexer_list);
	uncapitalize_cmd(lexer_list);

	/* free la lexer_list avant la fin de cette fonction */
}
