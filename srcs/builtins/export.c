/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:05 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/13 02:17:05 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_if_variable_exists(t_list *env, char *var, char *value)
{
	size_t	len;
	t_env	*tmp;

	len = ft_strlen(var);
	tmp = NULL;
	while (env)
	{
		tmp = ((t_env *)(env->content));
		if (!ft_strncmp(var, tmp->variable, len)
			&& ft_strlen(tmp->variable) == len)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

t_env	*new_env_entry(char *var, char *value)
{
	t_env	*new_entry;

	new_entry = malloc(sizeof(t_env));
	new_entry->variable = ft_strdup(var);
	if (value)
		new_entry->value = ft_strdup(value);
	return (new_entry);
}

void	exec_export(char *var, char *value)
{
	if (!var)
		print_env_in_ascii_order(g_all.env);
	else // cas où on export avec arguments 
	{
		if (!check_if_variable_exists(g_all.env, var, value))
			ft_lstadd_back(&(g_all.env), ft_lstnew(new_env_entry(var, value)));
	}
}

static void	set_var_and_value(char *str, char **var, char **value)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str) == 1 && !ft_strncmp(str, "=", 1))
	{
		send_error(PARSING, BAD_ASSIGN, NULL);
		exit(EXIT_FAILURE);
	}
	while (str[i])
	{
		if (str[i] == '=')
		{
			(*var) = ft_strndup(str, 0, i - 1);
			if (str[i + 1])
				(*value) = ft_strndup(str, i + 1, ft_strlen(str) - 1);
			break ;
		}
		i++;
	}
	if (i == ft_strlen(str))
	{
		(*var) = ft_strdup(str);
		(*value) = NULL;
	}
}

void	ft_export(char **args)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	var = NULL;
	value = NULL;
	if (args == NULL)
		exec_export(NULL, NULL);
	while (args && args[i])
	{
		set_var_and_value(args[i], &var, &value);
		exec_export(var, value);
		i++;
		if (value)
		{
			free(value);
			value = NULL;
		}
		if (var)
		{
			free(var);
			var = NULL;
		}
	}
}
