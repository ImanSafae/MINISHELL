#include "minishell.h"


t_cmd	*new_command(char *cmd, char *infile, char *outfile, int append)
{
	t_cmd	*command;
	int		i;

	command = malloc(sizeof(t_cmd));
	i = 0;
	if (infile)
		command->infile = ft_strdup(infile);
	if (outfile)
		command->outfile = ft_strdup(outfile);
	if (append == 1)
		command->append = 1;
	else
		command->append = 0;
	while (cmd[i] && !ft_isspace(cmd[i]))
		i++;
	command->command = ft_strndup(cmd, 0, i - 1);
	if (cmd[i] && ft_isspace(cmd[i]))
	{
		i++;
		command->args = ft_strndup(cmd, i, ft_strlen(cmd) - 1);
	}
	return (command);
}


void	split_list_on_pipes(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;

	tmp = (*lexer_list);
	caster = NULL;
	while (tmp)
	{
		caster = (t_lexer *)(tmp->content);
		while (tmp && caster->token != TOKEN_PIPE)
		{
			tmp = tmp->next;
			caster = (t_lexer *)(tmp->content);
		}
		if (caster->token == TOKEN_APPEND || caster->token == TOKEN_HEREDOC
			|| caster->token == TOKEN_INFILE || caster->token == TOKEN_OUTFILE)

		tmp = tmp->next;
	}
}

t_list	*tmp;
t_lexer	*caster;
char	*cmd;
char	*tmp2;

tmp = (*lexer_list);
while (tmp)
{
	caster = (t_lexer *)(tmp ->content);
	if (caster->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE
		|| caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR)
		cmd = ft_strjoin(caster->text, " ");
	while (tmp && caster->token != TOKEN_PIPE)
	{
		if (caster->token != TOKEN_APPEND && etc)
		{
			tmp2 = ft_strdup(cmd);
			free(cmd);
			cmd = ft_strjoin(tmp2, caster->text);
			free(tmp2);
		}
		tmp = tmp->next;
		caster = (t_lexer *)(tmp->content);
	}

	tmp = tmp->next;
}



// 1er élément
if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DQUOTE || caster->token == TOKEN_DOLLAR || caster->token == TOKEN_SQUOTE)
	cmd->command = caster->text;
else if (caster->token == TOKEN_PIPE)
