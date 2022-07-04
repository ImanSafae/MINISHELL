/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:17:42 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/04 17:50:34 by itaouil          ###   ########.fr       */
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

static char	*get_pathname(char *cmd, t_list *env) // TROUVE LE BON PATH POUR UNE COMMANDE DONNÉE ; RENVOIE NULL SI RIEN TROUVÉ ; IL FAUT LUI ENVOYER UNE COMMANDE SANS FLAGS
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

static int	replace_cmd_with_pathname(char **cmd, t_list *env)
{
	char	*cmd_pathname;

	cmd_pathname = get_pathname(*cmd, env);
	if (!cmd_pathname)
	{
		send_error(PARSING, UNKNOWN_COMMAND, *cmd);
		free(*cmd);
		return (0);
	}
	free(*cmd);
	(*cmd) = cmd_pathname;
	return (1);
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

static int	check_cmds_list(t_cmd *list, t_list *env)
{
	int		i;

	i = 0;
	while (list[i])
	{
		if (!check_if_builtin(list[i].command) && access(list[i].command, F_OK) == -1)
		{
			if (!replace_cmd_with_pathname(&(list[i].command), env))
				return (0);
		}
		// else if (check_if_builtin(list[i]->command))
		// {
			
		// }
		i++;
	}
	return (1);
}

int	check_infile(t_cmd command, int *infile, int cmd_id)
{
	if (command.infile)
	{
		(*infile) = open(command.infile, O_RDONLY);
		if ((*infile) == -1)
		{
			send_error(PARSING, WRONG_FILE, command.infile);
			return (0);
		}
		dup2(*infile, STDIN_FILENO);
	}
	return (1);
}

void	exec_cmd(t_cmd command)
{
	
	execve()
}

void	fork_and_exec(t_cmd *commands, int nb_of_pipes, int cmd_id)
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	pid_t	cpid;

	pipe(pipefd);
	cpid = fork();
	if (cpid == 0) // process fils dans lequel on va exécuter
	{
		//le fils va écrire, donc commencer par close l'extrémité de lecture
		close(pipefd[1]);
		/* commencer par s'occuper des redirections in :
		- si un infile est précisé, on dup2 l'entrée standard vers l'infile.
		- si pas d'infile et qu'on est dans la première commande, l'entrée reste l'entrée standard : pas besoin de dup2
		- si pas d'infile et qu'on n'est pas dans la première commande, l'entrée = la sortie du pipe précédent, le dup2 a déjà été fait par le process père */
		if (!check_infile(commands[cmd_id], &infile, cmd_id))
			return ;
		/* checker ensuite les redirections out :
		- si un outfile est précisé -> dup2 la sortie standard vers l'outfile
		*/
		if (commands->outfile)
		{
			if (commands->append == 1)
				outfile = open(commands->outfile, O_APPEND | O_CREAT, 0777);
			else
				outfile = open(commands->outfile, O_WRONLY | O_CREAT, 0777);
			dup2(outfile, STDOUT_FILENO);
		}
		/* - si aucun outfile n'est précisé :
		- la sortie standard reste la sortie standard dans le cas où on est dans la dernière commande
		- la sortie standard devient l'entrée du pipe dans le cas où on est dans une des commandes du milieu
		*/
		else if (cmd_id < nb_of_pipes)
		{
			outfile = pipefd[0];
			dup2(outfile, STDOUT_FILENO);
		}
		exec_cmd();
	}
	else // process parent dans lequel on va appeler en récursif tant qu'il y a des commandes à exécuter
	{
		// le parent va lire, donc commencer par close l'extrémité d'écriture
		close(pipefd[0]);
		wait(NULL);
		dup2(pipefd[1], STDIN_FILENO);
		if (cmd_id == nb_of_pipes)
			close(pipefd[1]);
	}
}

void	ft_exec(t_exec *instructions, t_list *env)
{
	int	cmd_id;

	cmd_id = 0;
	if (!check_cmds_list(&(instructions->commands), env))
		return ; // cas de commande inconnue
	if (instructions->pipes > 0)
	{
		while (cmd_id >= instructions->pipes)
		{
			fork_and_exec(instructions->commands, instructions->pipes, cmd_id);
			cmd_id++;
		}
	
	}
	else
}
