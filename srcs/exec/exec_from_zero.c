/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_from_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:17:42 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/02 19:22:18 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_pathtab(t_list *env)
{
	char	*path;
	char	**pathtab;

	path = ft_getenv(env, "PATH");
	pathtab = ft_split(path, ':');
	return (pathtab);
}

static char	*get_pathname(char *cmd, t_list *env) // TROUVE LE BON PATH POUR UNE COMMANDE DONNÉE ; RENVOIE NULL SI RIEN TROUVÉ ; I FAUT LUI ENVOYER UNE COMMANDE SANS FLAGS
{
	char	**pathtab;
	char	*cmd_suffix;
	char	*pathname;
	int		i;

	pathtab = get_pathtab(env);
	cmd_suffix = ft_strjoin("/", cmd);
	pathname = NULL;
	i = 0;
	while (pathtab && pathtab[i])
	{
		pathname = ft_strjoin(pathtab[i], cmd_suffix);
		if (!access(pathname, F_OK))
			break ;
		free(pathname);
		i++;
	}
	free_tab(pathtab);
	free(cmd_suffix);
	return (pathname);
}

static void	replace_cmd_with_pathname(char **cmd, t_list *env)
{
	char	*cmd_pathname;

	cmd_pathname = get_pathname(*cmd, env);
	free(*cmd);
	(*cmd) = cmd_pathname;
}

static int	check_if_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (1);
	if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (1);
	if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		return (1);
	if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		return (1);
	if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (1);
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (1);
	if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (1);
	return (0);
}

static void	check_cmds_list(t_cmd *list, t_list *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (list[i])
	{
		tmp = uncapi
		if (!check_if_builtin(list[i]->command) && access(list[i]->command, F_OK) == -1)
			replace_cmd_with_pathname(&(tmp->command), env);
		i++;
	}
}

void	ft_exec(t_exec *instructions, t_list *env)
{
	// int		infile;
	// int		outfile;

	// if (instructions->infile)
	// {
	// 	infile = open(instructions->infile, O_RDONLY);
	// 	if (infile == -1)
	// 		send_error(PARSING, WRONG_FILE, instructions->infile);
	// }
	// if (instructions->outfile)
	// {
	// 	if (instructions->append)
	// 		outfile = open(instructions->outfile, O_APPEND | O_CREAT);
	// 	else
	// 		outfile = open(instructions->outfile, O_WRONLY | O_CREAT);
	// }
	check_cmds_list(&(instructions->commands), env);

}
