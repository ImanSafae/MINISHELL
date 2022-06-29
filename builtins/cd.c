/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:45:04 by anggonza          #+#    #+#             */
/*   Updated: 2022/06/29 14:21:27 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_value(char *variable, char *value, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
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

char	*find_variable_in_env(char *str, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
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

void	change_oldpwd(char *path, t_list **env)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", path);
	if (find_variable_in_env("OLDPWD", env) == NULL)
		ft_lstadd_back(env, ft_lstnew(add_var_to_env(tmp)));
	else
		change_env_value("OLDPWD", path, env);
}

void	change_pwd(char *path, t_list **env)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", path);
	if (find_variable_in_env("PWD", env) == NULL)
		ft_lstadd_back(env, ft_lstnew(add_var_to_env(tmp)));
	else
		change_env_value("PWD", path, env);
	free(tmp);
}

void	cd(char *arg, t_list **env)
{
	char	*actual_path;
	char	*next_path;

	actual_path = malloc(256);
	next_path = malloc(256);
	actual_path = getcwd(actual_path, 256);
	if (!arg || ft_strlen(arg) == 0)
	{
		if (chdir(find_variable_in_env("HOME", env)) == -1)
			g_all.exit_code = 127;
		else
		{
			change_oldpwd(actual_path, env);
			change_pwd(find_variable_in_env("HOME", env), env);
			g_all.exit_code = 0;
		}
	}
	else
	{
		if (chdir(arg) == -1)
			g_all.exit_code = 127;
		else
		{
			change_oldpwd(actual_path, env);
			change_pwd(getcwd(next_path, 256), env);
			g_all.exit_code = 0;
		}
	}
}
