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
	else if (c == '<' && next != '<')
		return (TOKEN_INFILE);
	else if (c == '<' && next == '<')
		return (TOKEN_HEREDOC);
	else if (c == '>' && next != '>')
		return (TOKEN_OUTFILE);
	else if (c == '>' && next == '>')
		return (TOKEN_APPEND);
	else if (ft_isnotspecial(c) && !ft_isspace(c))
		return (TOKEN_TEXT);
	return (0);
}

static char	*retrieve_squoted_text(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	if (line[*i])
		ret = ft_chardup(line[*i]);
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		(*i)++;
		free(tmp);
		free(tmp2);
	}
	if (!line[*i])
		send_error(PARSING, OPEN_QUOTE, line);
	return (ret);
}

static char	*retrieve_dquoted_text(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	if (line[*i])
		ret = ft_chardup(line[*i]);
	(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		(*i)++;
		free(tmp);
		free(tmp2);
	}
	if (!line[*i])
		send_error(PARSING, OPEN_QUOTE, line);
	return (ret);
}

static char	*retrieve_variable(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	// if (line[*i + 1] && !ft_isspace(line[*i + 1]))
	// 	(*i)++;
	ret = ft_chardup(line[*i]);
	(*i)++;
	while (line[*i] && ft_isalnum(line[*i]) && !ft_isspace(line[*i]))
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		(*i)++;
	}
	return (ret);
}

static char	*retrieve_text(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	ret = ft_chardup(line[*i]);
	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	while (line[*i] && ft_isnotspecial(line[*i]) && !ft_isspace(line[*i]))
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		(*i)++;
		free(tmp);
		free(tmp2);
	}
	return (ret);
}


static char	*retrieve_flag(char *line, int *i)
{
	char	*ret;
	char	*tmp;

	ret = ft_chardup(line[*i]);
	tmp = NULL;
	(*i)++;
	while (line[*i] && !ft_isspace(line[*i]))
	{
		if (!ft_isnotspecial(line[*i]))
			break ;
		tmp = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(tmp, ft_chardup(line[*i]));
		free(tmp);
		(*i)++;
	}
	return (ret);
}

static char	*retrieve_redirection(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	tmp = ft_chardup(line[*i]);
	tmp2 = ft_chardup(line[*i + 1]);
	ret = ft_strjoin(tmp, tmp2);
	(*i)++;
	return (ret);
}

static char	*retrieve_filename(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	ret = NULL;
	tmp = NULL;
	tmp2 = NULL;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i])
	{
		ret = ft_chardup(line[*i]);
		(*i)++;
	}
	while (line[*i] && !ft_isspace(line[*i]) && ft_isnotspecial(line[*i]))
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		(*i)++;
	}
	return (ret);
}

void	interpret_token(char *line, int token, int *i, t_list **list)
{
	char	*content;
	char	*tmp;

	content = NULL;
	tmp = NULL;
	if (token == TOKEN_TEXT)
	{
		printf("token is text\n");
		content = retrieve_text(&(*line), i);
	}
	else if (token == TOKEN_SQUOTE)
	{
		printf("token is simple quote\n");
		content = retrieve_squoted_text(line, i);
	}
	else if (token == TOKEN_DQUOTE)
	{
		printf("token is double quote\n");
		content = retrieve_dquoted_text(line, i);
	}
	else if (token == TOKEN_DOLLAR)
	{
		printf("token is dollar\n");
		content = retrieve_variable(line, i);
	}
	else if (token == TOKEN_FLAG)
	{
		printf("token is flag\n");
		content = retrieve_flag(line, i);
	}
	else if (token == TOKEN_PIPE || token == TOKEN_INFILE)
	{
		printf("token is pipe or infile\n");
		content = retrieve_text(line, i);
	}
	else if (token == TOKEN_HEREDOC || token == TOKEN_APPEND)
	{
		printf("token is heredoc or append\n");
		content = retrieve_redirection(line, i);
	}
	else if (token == TOKEN_INFILE || token == TOKEN_OUTFILE)
	{
		printf("token is filename\n");
		content = retrieve_filename(line, i);
	}
	update_lexer_list(list, content, token);
}

void	ft_lexer(char *line, t_list **env)
{
	int		i;
	int		token;
	t_list	*lexer_list;

	i = 0;
	lexer_list = NULL;
	while (line[i])
	{
		token = identify_token(line[i], line[i + 1]);
		interpret_token(line, token, &i, &lexer_list);
		i++;
		while (ft_isspace(line[i]))
			i++;
	}
	print_lexer_list(lexer_list);
}
