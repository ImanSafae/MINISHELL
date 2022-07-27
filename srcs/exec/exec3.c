/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:30:24 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/27 10:53:00 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_infile(t_cmd command)
{
	int	infile;

	infile = 0;
	if (command.hd_delimiter)
	{
		infile = heredoc(command.hd_delimiter);
		unlink("/tmp/heredoc.tmp");
		close(g_all.fd_to_close);
	}
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

int	check_outfile(t_cmd command)
{
	int	outfile;

	if (command.outfile)
	{
		if (command.append == 1)
			outfile = open(command.outfile, O_APPEND | O_CREAT
					| O_WRONLY, 0777);
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

void	exec_builtins_utils(t_cmd command)
{
	if (!ft_strncmp(command.command, "pwd", 3))
		ft_pwd();
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

int	check_recur_and_input(int pipefd[2], int nb_of_pipes, int cmd_id, int input)
{
	if (input)
		close(input);
	if (cmd_id != nb_of_pipes)
		return (1);
	else
		close(pipefd[0]);
	return (0);
}
