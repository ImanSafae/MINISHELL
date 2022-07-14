/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:19:16 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/14 23:26:49 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc(char *delim)
{
	char	*line;
	int		tmp_file;

	tmp_file = open("/tmp/heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	g_all.fd_to_close = tmp_file;
	line = NULL;
	while (1)
	{
		line = readline("heredoc > ");
		if (!(ft_strncmp(line, delim, ft_strlen(delim)))
			&& (ft_strlen(delim) == ft_strlen(line)))
		{
			free(line);
			break ;
		}
		write(tmp_file, line, ft_strlen(line));
		write(tmp_file, "\n", 1);
		free(line);
	}
	g_all.heredoc = 1;
	return (tmp_file);
	// close(tmp_file);
}
