#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BLUE   "\001\e[0;34m\002"
# define WHITE  "\001\e[0;37m\002"
# define RED    "\001\e[0;31m\002"
# define YELLOW "\001\e[0;33m\002"
# define RESET  "\001\e[0m\002"
typedef struct s_env
{
	/* data */
}				t_env;

// ENV
char	**create_env(char **envp);
int		envlen(char **envp);
int		ft_strlenn(char **str);
void	rl_replace_line(const char *text, int clear_undo);
// LEXER

// PARSER

// BUILTINS

// EXECUTION

// UTILS

#endif