#include "minishell.h"

// int	identify_token(char c, char next)
// {
// 	if (c == '\"')
// 		return (TOKEN_DQUOTE);
// 	else if (c == '\'')
// 		return (TOKEN_SQUOTE);
// 	else if (c == '$')
// 		return (TOKEN_DOLLAR);
// 	else if (c == '|')
// 		return (TOKEN_PIPE);
// 	else if (c == '-')
// 		return (TOKEN_FLAG);
// 	else if (c == '*')
// 		return (TOKEN_WILDCARD);
// 	else if (c == '<' && next != '<')
// 		return (TOKEN_INFILE);
// 	else if (c == '<' && next == '<')
// 		return (TOKEN_HEREDOC);
// 	else if (c == '>' && next != '>')
// 		return (TOKEN_OUTFILE);
// 	else if (c == '>' && next == '>')
// 		return (TOKEN_APPEND);
// 	else if (ft_isalnum(c))
// 		return (TOKEN_TEXT);
// 	return (0);
// }

// char	*get_str_in_squotes(char *arg, int i)
// {
// 	char	*str;
// 	int		begin;
// 	int		end;

// 	str = NULL;
// 	begin = i;
// 	end = 0;
// 	while (arg[i] && arg[i] != '\'')
// 		i++;
// 	if (arg[i] && arg[i] != '\'')
// 		send_error(PARSING, OPEN_QUOTE, arg);
// 	end = i;
// 	str = ft_strndup(arg, begin, end);
// 	//printf("%s\n", str);
// 	return (str);
// }

// void	update_list(char *arg, int i, int token, t_list **lexer_list)
// {
// 	char	*data;

// 	data = NULL;
// 	if (token != TOKEN_TEXT && token != TOKEN_APPEND && token != TOKEN_HEREDOC)
// 		ft_lstadd_back(lexer_list, new_entry_with_token(token, arg[i]));
// 	else if (token == TOKEN_TEXT)
// 	{
// 		printf("getting str\n");
// 		data = get_str_in_squotes(arg, i);
// 	}
// 	// char	*data;

// 	// data = NULL;
// 	// if (token == TOKEN_SQUOTE)
// 	// 	data = get_str_in_squotes(arg, i + 1);
// 	// if (data)
// }

// void	tokeniser(char *arg, t_list **lexer_list)
// {
// 	int	token;
// 	int	i;

// 	i = 0;
// 	while (arg[i])
// 	{
// 		token = identify_token(arg[i], arg[i + 1]);
// 		printf("token = %d\n", token);
// 		update_list(arg, i, token, lexer_list);
// 		i++;
// 	}
// }

// void	ft_lexer(char *arg, t_list *env)
// {
// 	int	i;
// 	t_list	*lexer_list;

// 	i = 0;
// 	lexer_list = NULL;
// 	tokeniser(arg, &lexer_list);
// 	//print_lexer_list(lexer_list);
// }