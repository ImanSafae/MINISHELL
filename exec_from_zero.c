/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_from_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:17:42 by itaouil           #+#    #+#             */
/*   Updated: 2022/06/27 18:08:33 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_list *env, char *variable)
{
	t_env	*caster;
	size_t	len;
	char	*ret;

	caster = NULL;
	len = ft_strlen(variable);
	ret = NULL;
	while (env)
	{
		caster = (t_env *)(env->content);
		if (!ft_strncmp(variable, caster->variable, len) && ft_strlen(caster->variable) == len)
		{
			ret = caster->value;
			break ;
		}
		env = env->next;
	}
	return (ret);
}

char	**get_pathtab(t_list *env)
{
	char	*path;
	char	**pathtab;

	path = ft_getenv(env, "PATH");
	pathtab = ft_split(path, ':');
	return (pathtab);
}

char	*get_pathname(char *cmd, t_list *env) // TROUVE LE BON PATH POUR UNE COMMANDE DONNÉE ; RENVOIE NULL SI RIEN TROUVÉ ; I FAUT LUI ENVOYER UNE COMMANDE SANS FLAGS
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

void	ft_exec(t_exec *instructions, t_list *env)
{
	t_cmd	*cmds;
	int		infile;
	int		outfile;

	cmds = *(instructions->commands);
	if (instructions->infile)
	{	
		infile = open(instructions->infile, O_RDONLY);
		if (infile == -1)
			send_error(PARSING, WRONG_FILE, instructions->infile);
	}
	if (instructions->outfile)
	{
		if (instructions->append)
			outfile = open(instructions->outfile, O_APPEND | O_CREAT);
		else
			outfile = open(instructions->outfile, O_WRONLY | O_CREAT);
	}
	while (cmds)
	{
		if (access(cmds->command, F_OK) == -1)
		{
			free(cmds->command);
		}
		cmds = cmds->next;
	}
}
