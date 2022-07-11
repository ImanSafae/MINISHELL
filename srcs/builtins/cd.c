/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:45:04 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/12 01:24:31 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_value(char *variable, char *value)
{
	t_list	*tmp;

	tmp = g_all.env;
	while (tmp->next)
	{
		if (ft_strlen(variable) == ft_strlen(((t_env *)
					(tmp->content))->variable))
		{
			if (!ft_strncmp(variable, ((t_env *)(tmp->content))->variable,
				ft_strlen(variable)))
			{
				free((((t_env *)(tmp->content))->value));
				(((t_env *)(tmp->content))->value) = value;
			}
		}
		tmp = tmp->next;
	}
}

char	*find_variable_in_env(char *str)
{
	t_list	*tmp;

	tmp = g_all.env;
	while (tmp->next)
	{
		if (ft_strlen(str) == ft_strlen(((t_env *)(tmp->content))->variable))
		{
			if (!ft_strncmp(str, ((t_env *)(tmp->content))->variable,
				ft_strlen(str)))
				return (((t_env *)(tmp->content))->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_oldpwd(char *path)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", path);
	if (find_variable_in_env("OLDPWD") == NULL)
		ft_lstadd_back(&(g_all.env), ft_lstnew(add_var_to_env(tmp)));
	else
		change_env_value("OLDPWD", path);
}

void	change_pwd(char *path)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", path);
	if (find_variable_in_env("PWD") == NULL)
		ft_lstadd_back(&(g_all.env), ft_lstnew(add_var_to_env(tmp)));
	else
		change_env_value("PWD", path);
	free(tmp);
}

static void	cd(char **arg)
{
	char	*actual_path;
	char	*next_path;

	actual_path = getcwd(NULL, 0);
	if (!arg || ft_strlen(arg) == 0)
	{
		if (chdir(find_variable_in_env("HOME")) == -1)
			g_all.exit_code = 127;
		else
		{
			change_oldpwd(actual_path);
			change_pwd(find_variable_in_env("HOME"));
			g_all.exit_code = 0;
		}
	}
	else
	{
		if (chdir(arg) == -1)
			g_all.exit_code = 127;
		else
		{
			change_oldpwd(actual_path);
			change_pwd(getcwd(next_path, 0));
			g_all.exit_code = 0;
		}
	}
}

void	ft_cd(char **args)
{
	if (tab_length(args) > 1)
	{
		send_error(CD, TOO_MANY_ARGS, NULL);
		exit(EXIT_FAILURE);
	}
	if (args[0] && access(args[0], F_OK) == -1)
		send_error(CD, WRONG_FILE, args[0]);
	cd(&(args[0]));
}
