#include "minishell.h"

int	identify_token(char c, char next)
{
	if (c == '\"')
		return (TOKEN_DQUOTE);
	else if (c == '\'')
		return (TOKEN_SQUOTE);
	else if (c == '$')
		return (TOKEN_DOLLAR);
	else if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '-')
		return (TOKEN_FLAG);
	else if (c == '*')
		return (TOKEN_WILDCARD);
	else if (c == '<' && next != '<')
		return (TOKEN_INFILE);
	else if (c == '<' && next == '<')
		return (TOKEN_HEREDOC);
	else if (c == '>' && next != '>')
		return (TOKEN_OUTFILE);
	else if (c == '>' && next == '>')
		return (TOKEN_APPEND);
	else if (ft_isalnum(c))
		return (TOKEN_TEXT);
}

char	*get_str_in_squotes(char *arg, int i, t_list **lexer_list)
{
	char	*str;
	int		len;
	int		begin;
	int		end;

	str = NULL;
	len = 0;
	begin = i;
	end = 0;
	while (arg[i] != '\'')
	{
		i++;
	}
}

void	update_list(char *arg, int i, int token, t_list **lexer_list)
{
	char	*data;

	data = NULL;
	if (token == TOKEN_SQUOTE)
	{
		get_str_in_quotes(arg, i, lexer_list);
	}
}

void	tokeniser(char *arg, t_list **lexer_list)
{
	int	token;
	int	i;

	i = 0;
	while (arg[i])
	{
		token = identify_token(arg[i], arg[i + 1]);

		i++;
	}
}

void	ft_lexer(char *arg, t_list *env)
{
	int	i;
	t_list	*lexer_list;

	i = 0;
	lexer = malloc(sizeof(t_list));
	tokeniser(arg, &lexer_list);
	while (arg[i])
	{
	
		i++;
	}
}