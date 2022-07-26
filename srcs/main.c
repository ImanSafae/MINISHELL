/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:12 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/26 15:02:37 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_all	g_all;

static void	print_white_house(void)
{
	printf("\n\n\n\n\n                 _ _.-'`-._ _                  \n");
	printf("                ;.'________'.;                \n");
	printf("     _________n.[____________].n_________     \n");
	printf("    |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]    \n");
	printf("    |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|    \n");
	printf("    |LI LI LI LI||LI||LI||LI||LI LI LI LI|    \n");
	printf("    |.. .. .. ..||..||..||..||.. .. .. ..|    \n");
	printf("    |LI LI LI LI||LI||LI||LI||LI LI LI LI|    \n");
	printf(" ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,, \n");
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n\n");
	printf("Welcome. Minishell Obama has been waiting for you.\n\n\n\n\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*str;

	(void)argc;
	(void)argv;
	g_all.fd_to_close = -1;
	env = create_env(envp);
	g_all.env = env;
	g_all.in_command = 0;
	print_white_house();
	echo_control_seq(0);
	while (1)
	{
		detect_signals();
		str = readline("minishell obama is waiting for instructions > ");
		g_all.prompt = 1;
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(str) == 0)
			continue ;
		add_history(str);
		ft_lexer(str);
		free(str);
		g_all.prompt = 0;
	}
	clear_history();
	free_env(&env);
}

	//system("leaks minishell");
// COMMENTAIRE D'AU DESSUS
// ft_export(&env, "VARTEST", "lol");
	// ft_export(&env, NULL, NULL);
	//ft_unset("PATH=", &env);
	// ft_env(&env);


