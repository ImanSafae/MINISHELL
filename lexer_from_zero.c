#include "minishell.h"

void	move_iterator(char *str, int *i)
{
	while (str[*i] && ft_isnotspecial(str[*i]))
	(*i)++;
}

void	interpret_token(char **line, int token, int *i)
{
	if (token == TOKEN_TEXT)
	{
		move_iterator(*line, i);
	}
}

void	ft_lexer(char *line, t_list **env)
{
	int	i;
	int	token;

	i = 0;
	while (line[i])
	{
		token = identify_token(line[i], line[i + 1]);
		interpret_token(&line, token, &i);
	}
}