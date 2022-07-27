/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:17:42 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/27 10:51:33 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(t_cmd command, int forked)
{
	int	oldfd;

	oldfd = dup(STDOUT_FILENO);
	check_outfile(command);
	if (check_if_builtin(command.command))
		exec_builtins_utils(command);
	else
	{
		tab_addfront(&(command.args), command.command);
		execve(command.command, command.args, NULL);
	}
	if (forked == 1)
		exit(EXIT_SUCCESS);
	dup2(oldfd, STDOUT_FILENO);
}

void	check_presence_of_command(t_cmd command)
{
	if (command.command == NULL)
	{
		if (command.outfile)
			touch_outfile(command.outfile);
		exit(EXIT_SUCCESS);
	}
}

void	fork_and_exec(t_cmd *commands, int nb_of_pipes, int cmd_id, int input)
{
	int		pipefd[2];
	pid_t	cpid;

	pipe(pipefd);
	signal(SIGQUIT, sigquit);
	cpid = fork();
	if (cpid == 0)
	{
		close(pipefd[0]);
		dup2(input, STDIN_FILENO);
		if (!check_infile(commands[cmd_id]))
			return ;
		if (commands[cmd_id].outfile && !check_outfile(commands[cmd_id]))
			return ;
		else if (cmd_id < nb_of_pipes)
			dup2(pipefd[1], STDOUT_FILENO);
		check_presence_of_command(commands[cmd_id]);
		exec_cmd(commands[cmd_id], 1);
	}
	close(pipefd[1]);
	if (check_recur_and_input(pipefd, nb_of_pipes, cmd_id, input))
		fork_and_exec(commands, nb_of_pipes,
			cmd_id + 1, pipefd[0]);
}

void	ft_exec(t_exec *instructions)
{
	int	cmd_id;

	cmd_id = 0;
	if (!check_cmds_list(instructions->commands, instructions->pipes + 1))
		return ;
	echo_control_seq(1);
	g_all.in_command = 1;
	if (!instructions->pipes
		&& check_if_builtin(instructions->commands->command))
		exec_cmd(*instructions->commands, 0);
	else
		fork_and_exec((instructions->commands), instructions->pipes, cmd_id, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
	echo_control_seq(0);
	g_all.in_command = 0;
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
