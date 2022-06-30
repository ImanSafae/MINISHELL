#include "minishell.h"

char	*get_command(t_list *lexer_list, t_list **pointer) // C TROP LONG ET C MEME PAS FINI JE VAIS CABLER
{
	char	*ret;
	char	*temp;
	t_lexer	*caster;

	caster = (t_lexer *)((*pointer)->content);
	if (caster->token == TOKEN_TEXT) //rajouter les autres types de token qui correpsondent a du texte
		ret = ft_strdup(caster->text);
	(*pointer) = (*pointer)->next;
	while ((*pointer) && caster->token != TOKEN_PIPE)
	{
		if (caster->token == TOKEN_TEXT) // rajouter etc
		{
			temp = ft_strdup(ret);
			free(ret);
			ret = ft_strjoin_with_space(temp, caster->text);
			free(temp);
		}
		else if (caster->token == TOKEN_APPEND || caster->token == TOKEN_HEREDOC
			|| caster->token == TOKEN_INFILE || caster->token == TOKEN_OUTFILE)
		{
			// ajouter gestion de l'infile/outfile/append/heredoc
		}
		(*pointer) = (*pointer)->next;
		caster = (t_lexer *)((*pointer)->content);
	}
	return (ret);
}

void	split_list_on_pipes(t_list **lexer_list, int nb_of_pipes)
{
	t_list	*tmp;
	t_lexer	*caster;
	char	**command_line;
	int		i;

	tmp = (*lexer_list);
	caster = (t_lexer *)(tmp->content);
	command_line = malloc(sizeof(char *) * (nb_of_pipes + 1));
	i = 1;
	if (caster->token == TOKEN_PIPE)
	{
		free_tab(command_line);
		send_error(PARSING, NEAR, "|");
		return ;
	}
	command_line[0] = get_command(*lexer_list, &tmp);
	while (tmp)
	{
		if (caster->token == TOKEN_PIPE)
		{
			tmp = tmp->next;
			command_line[i] = get_command(*lexer_list, &tmp);
			i++;
		}
		// tmp = tmp->next;
	}
}
