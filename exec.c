#include "minishell.h"

/* EXECUTION
-

*/

char	*get_flags(char *cmd)
{

}

char	*trim_command(char *cmd)
{

}

char	**split_path(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{

		tmp = tmp->next;
	}
}



char	*get_pathname(char *cmd, t_list *env)
{
	char	*cmd_without_flags;
	char	*pathname;
	char	**path;
	char	*path_to_try;
	int		i;

	cmd_without_flags = trim_command(cmd);
	pathname = NULL;
	i = 0;
	path_to_try = NULL;
	if (!access(cmd_without_flags, R_OK))
		return (cmd_without_flags);
	else
	{
		while (path && path[i])
		{
			path_to_try = ft_strjoin(path[i], cmd_without_flags);
			if (!access())
			i++;
		}
	}
}

char	*check_if_builtin(char *cmd)
{

}

void exec(t_cmd *cmd, t_list *env)
{
	/*
	Execution d'une seule commande : 
	Le but est d'abord de créer un double tableau qui contient la commande d'un coté (sous forme de chemin absolu) et ses flags de l'autre.

	Exemple : Je reçois "ls -la", je veux créer un double tableau qui contient "/bin/ls" et "-la".
	On commence donc par créer un char* cmd_path et un char* flags
	*/
}

int main()
{
	//coder en dur ma var v correspondaNT A cat < hello > outfile | ls -l
	exec(v)
}
