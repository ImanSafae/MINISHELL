/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:17:42 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/14 23:16:01 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_pathtab(t_list *env)
{
	char	*path;
	char	**pathtab;

	path = ft_getenv(env, "PATH");
	if (path == NULL)
		return (NULL);
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

static int	replace_cmd_with_pathname(char **cmd)
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

static int	check_if_builtin(char *cmd)
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

static int	check_cmds_list(t_cmd *list, int nb_of_cmds)
{
	int		i;

	i = 0;
	while (i < nb_of_cmds)
	{
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

int	check_infile(t_cmd command)
{
	int	infile;

	infile = 0;
	if (command.hd_delimiter)
		infile = heredoc(command.hd_delimiter);
	if (command.infile)
	{
		infile = open(command.infile, O_RDONLY, 0777);
		if (infile == -1)
		{
			send_error(PARSING, WRONG_FILE, command.infile);
			return (0);
		}
		dup2(infile, STDIN_FILENO);
	}
	return (1);
}

void	exec_cmd(t_cmd command)
{
	if (check_if_builtin(command.command))
	{
		if (!ft_strncmp(command.command, "pwd", 3))
			ft_pwd(command.args);
		if (!ft_strncmp(command.command, "cd", 2))
			ft_cd(command.args);
		if (!ft_strncmp(command.command, "export", 6))
			ft_export(command.args);
		if (!ft_strncmp(command.command, "env", 3))
			ft_env(command.args);
		if (!ft_strncmp(command.command, "unset", 5))
			ft_unset(command.args);
		if (!ft_strncmp(command.command, "echo", 4))
			ft_echo(command.args);
		if (!ft_strncmp(command.command, "exit", 4))
			ft_exit(command.args);
	}
	else
	{
		tab_addfront(&(command.args), command.command);
		execve(command.command, command.args, NULL);
	}
}

static int	check_outfile(t_cmd command)
{
	int	outfile;

	if (command.outfile)
	{
		if (command.append == 1)
			outfile = open(command.outfile, O_APPEND | O_CREAT, 0777);
		else
			outfile = open(command.outfile, O_WRONLY | O_CREAT, 0777);
		if (outfile == -1)
		{
			send_error(PARSING, WRONG_FILE, command.outfile);
			return (0);
		}
		dup2(outfile, STDOUT_FILENO);
	}
	return (1);
}

void	fork_and_exec(t_cmd *commands, int nb_of_pipes, int cmd_id, int input)
{
	int		pipefd[2];
	pid_t	cpid;

	pipe(pipefd);
	cpid = fork();
	if (cpid == 0) // process fils dans lequel on va exécuter
	{
		close(pipefd[0]);
		dup2(input, STDIN_FILENO);
		if (!check_infile(commands[cmd_id]))
			return ;
		if (commands[cmd_id].outfile && !check_outfile(commands[cmd_id]))
			return ;
		else if (cmd_id < nb_of_pipes)
			dup2(pipefd[1], STDOUT_FILENO);
		exec_cmd(commands[cmd_id]);
		exit(EXIT_SUCCESS);
	}// process parent dans lequel on va appeler en récursif tant qu'il y a des commandes à exécuter
	close(pipefd[1]);
	if (input)
		close(input);
	if (cmd_id != nb_of_pipes)
		fork_and_exec(commands, nb_of_pipes,
			cmd_id + 1, pipefd[0]);
	else
		close(pipefd[0]);
}

void	ft_exec(t_exec *instructions)
{
	int	cmd_id;

	cmd_id = 0;
	if (!(instructions->commands->command))
	{
		printf("Warning : trying to execute with no command !\n");
		return ;
	}
	if (!check_cmds_list(instructions->commands, instructions->pipes + 1))
		return ; // cas de commande inconnue
	if (!instructions->pipes && check_if_builtin(instructions->commands->command))
		exec_cmd(*instructions->commands);
	else
		fork_and_exec((instructions->commands), instructions->pipes, cmd_id, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	touch_outfile(char	*outfile)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	command->append = 0;
	command->nb_of_cmds = 1;
	command->outfile = NULL;
	command->infile = NULL;
	command->hd_delimiter = NULL;
	command->command = ft_strdup("touch");
	command->args = malloc(sizeof(char *) * 2);
	command->args[0] = outfile;
	command->args[1] = NULL;
	replace_cmd_with_pathname(&(command->command));
	fork_and_exec(command, 0, 0, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
	free(command->args);
	free(command->command);
	free(command);
}
