/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:45:04 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/26 15:23:44 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_value(char *variable, char *value)
{
	t_list	*tmp;
	char	*val;

	tmp = g_all.env;
	val = ft_strdup(value);
	while (tmp->next)
	{
		if (ft_strlen(variable) == ft_strlen(((t_env *)
					(tmp->content))->variable))
		{
			if (!ft_strncmp(variable, ((t_env *)(tmp->content))->variable,
				ft_strlen(variable)))
			{
				free((((t_env *)(tmp->content))->value));
				(((t_env *)(tmp->content))->value) = val;
			}
		}
		tmp = tmp->next;
	}
}

void	change_oldpwd(char *path)
{
	char	*tmp;

	if (!path || access(path, F_OK) == -1)
		return ;
	tmp = ft_strjoin("OLDPWD=", path);
	if (find_variable_in_env("OLDPWD") == NULL)
		ft_lstadd_back(&(g_all.env), ft_lstnew(add_var_to_env(tmp)));
	else
		change_env_value("OLDPWD", path);
	free(tmp);
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

static void	cd(char *arg)
{
	char	*actual_path;
	char	*next_path;

	actual_path = getcwd(NULL, 0);
	if (!actual_path)
		return ;
	if (!arg || ft_strlen(arg) == 0)
	{
		change_oldpwd(actual_path);
		change_pwd(find_variable_in_env("HOME"));
		g_all.exit_code = 0;
	}
	else
	{
		chdir(arg);
		next_path = getcwd(NULL, 0);
		change_oldpwd(actual_path);
		change_pwd(next_path);
		g_all.exit_code = 0;
		free(next_path);
	}
	free(actual_path);
}

void	ft_cd(char **args)
{
	if (!args)
	{
		if (chdir(find_variable_in_env("HOME")) == -1)
		{
			send_error(CD, NO_HOME, NULL);
			g_all.exit_code = 1;
			return ;
		}
		cd("");
		return ;
	}
	if (tab_length(args) > 1)
	{
		send_error(CD, TOO_MANY_ARGS, NULL);
		return ;
	}
	if (args[0] && access(args[0], F_OK) == -1)
	{
		send_error(CD, WRONG_FILE, args[0]);
		g_all.exit_code = 127;
		return ;
	}
	cd(args[0]);
}
