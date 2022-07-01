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

void	parse_redirections(int token, t_cmd **command, char *file)
{
	if (token == TOKEN_APPEND)
		(*command)->append = 1;
	if (token == TOKEN_INFILE)
		(*command)->infile = ft_strdup(file);
	if (token == TOKEN_OUTFILE)
		(*command)->outfile = ft_strdup(file);
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

char	*get_command(t_list *lexer_list, t_list **pointer, t_cmd **cmd)
{
	char	*ret;
	t_lexer	*caster;

	caster = (t_lexer *)((*pointer)->content);
	if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
		|| caster->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
	{
		ret = ft_strdup(caster->text);
		(*pointer) = (*pointer)->next;
	}
	while ((*pointer) && caster->token != TOKEN_PIPE)
	{
		if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
			|| caster ->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
			add_text_to_string(&ret, caster->text);
		else if (caster->token == TOKEN_APPEND || caster->token == TOKEN_HEREDOC
			|| caster->token == TOKEN_INFILE || caster->token == TOKEN_OUTFILE)
			parse_redirections(caster->token, cmd, caster->text);
		(*pointer) = (*pointer)->next;
		caster = (t_lexer *)((*pointer)->content);
	}
	return (ret);
}

t_cmd	**split_list_on_pipes(t_list **lexer_list, int nb_of_pipes)
{
	t_cmd	*command;
	t_list	*tmp;
	t_lexer	*caster;
	int		i;

	command = malloc(sizeof(t_cmd *) * (nb_of_pipes + 1));
	tmp = (*lexer_list);
	caster = (t_lexer *)(tmp->content);
	i = 1;
	command[0].command = get_command(*lexer_list, &tmp, &command[0]);
	while (tmp)
	{
		if (caster->token == TOKEN_PIPE)
		{
			tmp = tmp->next;
			command[i].command = get_command(*lexer_list, &tmp, &command[i]);
			i++;
		}
		tmp = tmp->next;
	}
	return (command);
}

void	ft_parser(t_list **lexer_list, t_list *env)
{
	int		nb_of_pipes;
	t_exec	*exec;
	t_cmd	*cmd;

	nb_of_pipes = count_pipes(*lexer_list);
	exec = malloc(sizeof(t_exec));
	if (((t_lexer *)((*lexer_list)->content))->token == TOKEN_PIPE)
	{
		send_error(PARSING, NEAR, "|");
		return ;
	}
	cmd = split_list_on_pipes(lexer_list, nb_of_pipes);
	exec->commands = cmd;
	exec->pipes = nb_of_pipes;
	print_commands_tab(&cmd, nb_of_pipes);
}
