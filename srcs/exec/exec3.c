/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:30:24 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/26 16:18:28 by itaouil          ###   ########.fr       */
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
		printf("Opening file descriptor %d\n", infile);
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
			outfile = open(command.outfile, O_APPEND | O_CREAT | O_WRONLY, 0777);
		else
			outfile = open(command.outfile, O_WRONLY | O_CREAT, 0777);
		printf("Opening file descriptor %d\n", outfile);
		if (outfile == -1)
		{
			send_error(PARSING, WRONG_FILE, command.outfile);
			return (0);
		}
		dup2(outfile, STDOUT_FILENO);
	}
	return (1);
}
