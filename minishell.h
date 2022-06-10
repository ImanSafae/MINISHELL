/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:51 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/10 20:55:09 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*variable;
	char	*value;
}				t_env;

typedef struct s_lexer
{
	char	*data;
	int		token;
}				t_lexer;

typedef struct s_token
{
	char	c;
	int		type;
}				t_token;

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


// ERRORS: FUNCTIONS
# define EXIT 0

// ERRORS: ERROR CODES
# define NUM 0
# define TOO_MANY_ARGS 1

// ENV
t_list	*create_env(char **envp);
int		envlen(char **envp);
void	rl_replace_line(const char *text, int clear_undo);
void	delete_element(void *element);

// ERROR
void	send_error(int function, int error, char *arg);

// LEXER



// PARSER

// BUILTINS
void	ft_unset(char	*variable, t_list **env);
void	ft_export(t_list **env, char *var, char *value);
void	print_env_in_ascii_order(t_list *env);
void	ft_env(t_list **env);
//void	ft_free_list(t_list **liste);
t_env	*new_env_entry(char *var, char *value);
void	ft_pwd();

// EXECUTION

// UTILS
void	delete_element_from_list(t_list **previous, t_list **to_delete);
t_list	*duplicate_list(t_list *list);
t_env	*duplicate_line(t_env *line);

// FREE
void	free_list(t_list **list);
void	free_element(void *element);
void	free_tab(char **tab);
void	empty_env_element(void *element);

// TESTS (à supprimer à la fin)
//void	print_env(t_list *env);

#endif
