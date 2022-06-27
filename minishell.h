/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:51 by anggonza          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/27 16:34:44 by itaouil          ###   ########.fr       */
=======
/*   Updated: 2022/06/27 14:55:28 by anggonza         ###   ########.fr       */
>>>>>>> 5b88ed61cdcd233b9ac54742b73ad7ba6ad2d9b9
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BLUE   "\001\e[0;34m\002"
# define WHITE  "\001\e[0;37m\002"
# define RED    "\001\e[0;31m\002"
# define YELLOW "\001\e[0;33m\002"
# define RESET  "\001\e[0m\002"

typedef struct s_all
{
	int	exit_code;
}	t_all;

typedef struct s_env
{
	char	*variable;
	char	*value;
}				t_env;

typedef struct s_lexer
{
	char	*text;
	int		token;
}				t_lexer;

typedef struct s_cmd
{
	char			*command;
	char			*flags;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_exec
{
	int		pipes;
	t_cmd	**commands;
	char	*infile;
	char	*outfile;
	int		append;
}				t_exec;

// typedef struct s_token
// {
// 	char	c;
// 	int		type;
// }				t_token;

// TOKENS
# define TOKEN_DQUOTE 0
# define TOKEN_SQUOTE 1
# define TOKEN_PIPE 2
# define TOKEN_DOLLAR 3
# define TOKEN_INFILE 4
# define TOKEN_OUTFILE 5
# define TOKEN_SPACE 6
# define TOKEN_HEREDOC 7
# define TOKEN_APPEND 8
# define TOKEN_TEXT 9
# define TOKEN_WILDCARD 10
# define TOKEN_FLAG 11
# define TOKEN_QUOTED_TEXT 12

// ERRORS: FUNCTIONS
# define PARSING 0
# define EXIT 1

// ERRORS: ERROR CODES
# define NUM 0
# define TOO_MANY_ARGS 1
# define OPEN_QUOTE 2
# define WRONG_FILE 3

// ENV
t_list	*create_env(char **envp);
int		envlen(char **envp);
void	rl_replace_line(const char *text, int clear_undo);
void	delete_element(void *element);

// ERROR
void	send_error(int function, int error, char *arg);

// LEXER
t_list	*new_entry_with_token(int token, char *str);
void	ft_lexer(char *line, t_list **env);
void	update_lexer_list(t_list **list, char *text, int token);

// PARSER

// BUILTINS
void	ft_unset(char	*variable, t_list **env);
void	ft_export(t_list **env, char *var, char *value);
void	print_env_in_ascii_order(t_list *env);
void	ft_env(t_list **env);
t_env	*new_env_entry(char *var, char *value);
void	ft_pwd(void);
void	cd(char *arg);

//EXPAND
void	expand_variable(char **value, t_list **env);

// EXECUTION

// UTILS
void	delete_element_from_list(t_list **previous, t_list **to_delete);
t_list	*duplicate_list(t_list *list);
t_env	*duplicate_line(t_env *line);
char	*ft_strndup(char *str, int begin, int end);
int		ft_isnotspecial(char c);
int		ft_isspace(char c);
char	*ft_chardup(char c);
void	detect_signals(void);

// FREE
void	free_env(t_list **list);
void	free_element(void *element);
void	free_tab(char **tab);
void	free_lexer(t_list **lexer);
void	empty_env_element(void *element);

// TESTS (à supprimer à la fin)
//void	print_env(t_list *env);
void	print_lexer_list(t_list *list);

#endif
