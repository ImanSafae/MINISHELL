/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:51 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/06 18:32:37 by anggonza         ###   ########.fr       */
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

typedef struct s_token
{
	char	c;
	int		type;
}				t_token;
// ENV
t_list	*create_env(char **envp);
int		envlen(char **envp);
void	rl_replace_line(const char *text, int clear_undo);
void	delete_element(void *element);

// LEXER

// PARSER

// BUILTINS
void	ft_unset(char	*variable, t_list **env);
void	ft_export(t_list **env, char *var, char *value);
void	print_env_in_ascii_order(t_list *env);
void	ft_env(t_list **env);
//void	ft_free_list(t_list **liste);
t_env	*new_env_entry(char *var, char *value);

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
