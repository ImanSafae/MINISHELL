/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:34:57 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/03 20:56:53 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parsing_errors(int error, char *arg) // REMPLACER LES PRINTF PAR DES PUTSTR QUI ECRIVENT DANS STDERR
{
	if (error == OPEN_QUOTE)
		printf("Error : unclosed quote\n");
	else if (error == WRONG_FILE)
		printf("%s: No such file or directory\n", arg);
	else if (error == NEAR)
		printf("parse error near '%s'\n", arg);
	// exit(EXIT_FAILURE);
}

static void	exit_errors(int error, char *arg)
{
	printf("exit: ");
	if (error == NUM)
		printf("%s : numeric argument required\n", arg);
	else if (error == TOO_MANY_ARGS)
		printf("too many arguments\n");
}

void	send_error(int function, int error, char *arg)
{
	printf("minishell-obama: ");
	if (function == EXIT)
		exit_errors(error, arg);
	else if (function == PARSING)
		parsing_errors(error, arg);
}
