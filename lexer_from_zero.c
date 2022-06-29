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
	// else if (c == '-')
	// 	return (TOKEN_FLAG);
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

static char	*retrieve_variable(char *line, int *i, int single_quoted,
		t_list **env)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	ret = ft_chardup(line[*i]);
	(*i)++;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_')
		&& !ft_isspace(line[*i]))
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		(*i)++;
	}
	if (!single_quoted)
		expand_variable(&ret, env);
	return (ret);
}

char	*find_end(char *line, int i)
{
	char	*end;

	while (line[i] && !ft_isspace(line[i]))
		i++;
	end = ft_substr(line, i, ft_strlen(line) - i);
	return (end);
}

char	*check_for_envvar(char *line, t_list **env)
{
	int		i;
	char	*end;
	char	*begin;
	char	*tmp;
	int		before_var;

	i = 0;
	end = NULL;
	begin = NULL;
	tmp = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			before_var = i;
			end = find_end(line, i + 1);
			begin = ft_strndup(line, 0, i - 1);
			line = retrieve_variable(line, &i, 0, env);
			tmp = ft_strjoin(begin, line);
			line = ft_strjoin(tmp, end);
			free(tmp);
			free(end);
			free(begin);
			i = before_var;
		}
		i++;
	}
	return (line);
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

void	get_index(char *line, int *i)
{
	while (line[*i] && line[*i] != '\"')
		(*i)++;
}
static char	*retrieve_dquoted_text(char *line, int *i, t_list **env)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	char	*line_tmp;
	int		i_tmp;

	tmp = NULL;
	tmp2 = NULL;
	(*i)++;
	i_tmp = *i;
	tmp = ft_strndup(line, 0, i_tmp - 1);
	line_tmp = ft_strjoin(tmp, check_for_envvar(&(line[i_tmp]), env));
	free(tmp);
	if (line_tmp[i_tmp])
		ret = ft_chardup(line_tmp[i_tmp]);
	i_tmp++;
	get_index(line, i);
	while (line_tmp[i_tmp] && line_tmp[i_tmp] != '\"')
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line_tmp[i_tmp]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		i_tmp++;
		free(tmp);
		free(tmp2);
	}
	if (!line_tmp[i_tmp])
		send_error(PARSING, OPEN_QUOTE, line);
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
	(*i)--;
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

void interpret_token(char *line, int token, int *i, t_list **list, t_list **env)
{
	char	*content;
	int		single_quoted;

	content = NULL;
	single_quoted = 0;
	if (token == TOKEN_TEXT)
	{
		printf("token is text\n");
		content = retrieve_text(&(*line), i);
	}
	else if (token == TOKEN_SQUOTE)
	{
		printf("token is simple quote\n");
		single_quoted = 1;
		content = retrieve_squoted_text(line, i);
	}
	else if (token == TOKEN_DQUOTE)
	{
		printf("token is double quote\n");
		content = retrieve_dquoted_text(line, i, env);
	}
	else if (token == TOKEN_DOLLAR)
	{
		printf("token is dollar\n");
		content = retrieve_variable(line, i, single_quoted, env);
	}
	// else if (token == TOKEN_FLAG)
	// {
	// 	printf("token is flag\n");
	// 	content = retrieve_flag(line, i);
	// }
	else if (token == TOKEN_PIPE)
	{
		content = ft_chardup(line[*i]);
		printf("token is pipe\n");
		// content = retrieve_text(line, i);
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
		interpret_token(line, token, &i, &lexer_list, env);
		i++;
		while (ft_isspace(line[i]))
			i++;
	}
	print_lexer_list(lexer_list);
	free_lexer(&lexer_list);
}
