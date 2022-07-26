/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:34:57 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/26 14:09:36 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parsing_errors(int error, char *arg)
{
	if (error == OPEN_QUOTE)
		ft_putstr_fd("Error : unclosed quote\n", 2);
	else if (error == WRONG_FILE)
	{
		printf("no such file or directory: %s\n", arg);
		g_all.exit_code = 1;
	}
	else if (error == NEAR)
		printf("parse error near '%s'\n", arg);
	else if (error == BAD_ASSIGN)
		ft_putstr_fd("bad assignment\n", 2);
	else if (error == UNKNOWN_COMMAND)
	{
		printf("%s: command not found\n", arg);
		g_all.exit_code = 127;
	}
	else if (error == UNEXPECTEDTOK)
	{
		printf("syntax error near unexpected token `%s'\n", arg);
		g_all.exit_code = 258;
	}
}

static void	print_error(int error, char *arg)
{
	if (error == TOO_MANY_ARGS)
		ft_putstr_fd("too many arguments\n", 2);
	else if (error == NUM)
		printf("%s : numeric argument required\n", arg);
	else if (error == WRONG_FILE)
	{
		printf("no such file or directory: %s\n", arg);
		g_all.exit_code = 1;
	}
	else if (error == NO_HOME)
		ft_putstr_fd("HOME not set\n", 2);
}

static void	print_faulted_function_name(int function)
{
	if (function == EXIT)
		ft_putstr_fd("exit :", 2);
	else if (function == CD)
		ft_putstr_fd("cd : ", 2);
	else if (function == ENV)
		ft_putstr_fd("env :", 2);
}

void	send_error(int function, int error, char *arg)
{
	ft_putstr_fd("minishell-obama: ", 2);
	if (function == PARSING)
	{
		parsing_errors(error, arg);
		return ;
	}
	print_faulted_function_name(function);
	print_error(error, arg);
	
}
