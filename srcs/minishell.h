/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:51 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/21 20:55:42 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
#include <sys/wait.h>
# include <fcntl.h>

# define BLUE   "\001\e[0;34m\002"
# define WHITE  "\001\e[0;37m\002"
# define RED    "\001\e[0;31m\002"
# define YELLOW "\001\e[0;33m\002"
# define RESET  "\001\e[0m\002"

typedef struct s_all
{
	int		exit_code;
	int		fd_to_close;
	t_list	*env;
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
	int		space;
}				t_lexer;

typedef struct s_cmd
{
	char			*command;
	char			**args;
	char			*infile;
	char			*outfile;
	char			*hd_delimiter;
	int				append;
	int				nb_of_cmds;
}				t_cmd;

typedef struct s_exec
{
	int		pipes;
	t_cmd	*commands;
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

// ERRORS: FUNCTIONS
# define PARSING 0
# define EXIT 1
# define PWD 2
# define ENV 3
# define UNSET 4
# define CD 5

// ERRORS: ERROR CODES
# define NUM 0
# define TOO_MANY_ARGS 1
# define OPEN_QUOTE 2
# define WRONG_FILE 3
# define NEAR 4
# define UNKNOWN_COMMAND 5
# define NOT_ENOUGH_ARGS 6
# define BAD_ASSIGN 7
# define ERROR_CHAR "error"
# define OPEN_REDIRECTION 8
# define UNEXPECTEDTOK 9
// REDIRECTIONS
# define INFILE 0
# define OUTFILE 1

// ENV
t_list	*create_env(char **envp);
int		envlen(char **envp);
void	rl_replace_line(const char *text, int clear_undo);
void	delete_element(void *element);

// ERROR
void	send_error(int function, int error, char *arg);
int		check_error(char *line, int error);
int		check_error_or_update(char *content, t_list **list, int token);
void	all_check_errors(char *line, int *error);
// LEXER
t_list	*new_entry_with_token(int token, char *str);
void	ft_lexer(char *line);
void	update_lexer_list(t_list **list, char *text, int token);
int		retrieve_variable(char **content, char *line, int *i, int single_quoted);
char	*retrieve_squoted_text(char *line, int *i);
char	*retrieve_dquoted_text(char *line, int *i);
char	*retrieve_text(char *line, int *i);
char	*retrieve_filename(char *line, int *i);
char	*retrieve_heredoc(char *line, int *i);
char	*check_for_envvar(char *line);

// PARSER
void	ft_parser(t_list **lexer_list);

// BUILTINS
void	ft_unset(char **args);
void	ft_export(char **args);
void	print_env_in_ascii_order(t_list *env);
void	ft_env(char **args);
t_env	*new_env_entry(char *var, char *value);
void	ft_pwd(void);
void	ft_cd(char **args);
void	ft_echo(char **args);
void	ft_exit(char **args);

//EXPAND
int		expand_variable(char **value);
void	join_quotes_and_text(t_list **lexer_list);

// EXECUTION
void	ft_exec(t_exec *instructions);
void	touch_outfile(char	*outfile);
int		heredoc(char *delim);

// UTILS
void	delete_element_from_list(t_list **previous, t_list **to_delete, t_env **line);
t_list	*duplicate_list(t_list *list);
t_env	*duplicate_env_line(t_env *line);
char	*ft_strndup(char *str, int begin, int end);
int		ft_isnotspecial(char c);
int		ft_isspace(char c);
char	*ft_chardup(char c);
void	detect_signals(void);
char	*ft_getenv(t_list *env, char *variable);
char	*uncapitalize_str(char *str);
char	*ft_strndup(char *str, int start, int end);
char	*ft_strjoin_with_space(char *s1, char *s2);
int		count_pipes(t_list *list);
t_env	*add_var_to_env(char *line);
char	*find_variable_in_env(char *str);
void	change_env_value(char *variable, char *value);
void	uncapitalize_cmd(t_list **lexer_list);
void	tab_addfront(char ***tab, char *to_add);
int		tab_length(char **tab);
void	get_index(char *line, int *i, int type);
char	*find_end(char *line, int i);
void	check_for_heredoc(char *line, int *i, int *into_quote);
int		heredoc_quoted(char *line, int *i, int *into_quote);
void	determine_tmp2_value(char *line, int *i, char **tmp2);
char	*dquoted_utils(char *line, int *i, int *i_tmp, char **tmp);
void	check_unclose_dquoted(char *line_tmp, int i_tmp, char **ret, int *i);
int		squote_utils(char *line, int *i, int i_tmp, char **ret);
void	check_unclose_squoted(char *line, char **ret, int *i);
void	check_sometoken(char *line, int token, char **content, int *i);
int		check_doublequote(char *line, int *i);
int		count_quote(char *line, int type);
int		check_singlequote(char *line, int *i, int *i_tmp);
char	*get_next_word(char *str, int *index);

// FREE
void	free_env(t_list **list);
void	free_element(void *element);
void	free_tab(char **tab);
void	free_lexer(t_list **lexer);
void	empty_env_element(void *element);
void	free_exec_structs(t_exec **struc);
void	empty_lexer_element(void *element);

// TESTS (à supprimer à la fin)
//void	print_env(t_list *env);
void	print_lexer_list(t_list *list);
void	print_commands_tab(t_cmd *commands, int nb_of_pipes);

// VARIABLE GLOBALE
extern t_all	g_all;

#endif
