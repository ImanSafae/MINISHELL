/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:27:18 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/26 15:37:47 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_pathtab(t_list *env)
{
	char	*path;
	char	**pathtab;

	path = ft_getenv(env, "PATH");
	if (path == NULL)
		return (NULL);
	pathtab = ft_split(path, ':');
	return (pathtab);
}

char	*get_pathname(char *cmd, t_list *env)
{
	char	**pathtab;
	char	*cmd_suffix;
	char	*pathname;
	int		i;

	pathtab = get_pathtab(env);
	if (pathtab == NULL)
		return (NULL);
	cmd_suffix = ft_strjoin("/", cmd);
	pathname = NULL;
	i = 0;
	while (pathtab && pathtab[i])
	{
		pathname = ft_strjoin(pathtab[i], cmd_suffix);
		if (!access(pathname, F_OK))
			break ;
		free(pathname);
		pathname = NULL;
		i++;
	}
	free_tab(pathtab);
	free(cmd_suffix);
	return (pathname);
}

int	replace_cmd_with_pathname(char **cmd)
{
	char	*cmd_pathname;

	cmd_pathname = get_pathname(*cmd, g_all.env);
	if (!cmd_pathname)
	{
		send_error(PARSING, UNKNOWN_COMMAND, *cmd);
		free(*cmd);
		(*cmd) = NULL;
		return (0);
	}
	free(*cmd);
	(*cmd) = cmd_pathname;
	return (1);
}

int	check_if_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen("cmd")) && ft_strlen(cmd) == 4)
		return (1);
	if (!ft_strncmp(cmd, "exit", ft_strlen("exit")) && ft_strlen(cmd) == 4)
		return (1);
	if (!ft_strncmp(cmd, "env", ft_strlen("env")) && ft_strlen(cmd) == 3)
		return (1);
	if (!ft_strncmp(cmd, "export", ft_strlen("export")) && ft_strlen(cmd) == 6)
		return (1);
	if (!ft_strncmp(cmd, "unset", ft_strlen("unset")) && ft_strlen(cmd) == 5)
		return (1);
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd")) && ft_strlen(cmd) == 2)
		return (1);
	if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")) && ft_strlen(cmd) == 3)
		return (1);
	return (0);
}

int	check_cmds_list(t_cmd *list, int nb_of_cmds)
{
	int		i;

	i = 0;
	while (i < nb_of_cmds)
	{
		if (!list[i].command)
			i++;
		if (i >= nb_of_cmds)
			break ;
		if (!check_if_builtin(list[i].command)
			&& access(list[i].command, F_OK) == -1)
		{
			if (!replace_cmd_with_pathname(&(list[i].command)))
				return (0);
		}
		i++;
	}
	return (1);
}
