/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:14 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/13 01:31:29 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

static int	comes_first_in_ascii(char *one, char *two)
{
	int	i;

	i = 0;
	if (!two)
	{
		printf("\n\n\nhere\n\n\n");
		return (1);
	}
	while (one[i] && two[i])
	{
		if (one[i] < two[i])
			return (1);
		else if (two[i] < one[i])
			return (2);
		else
			i++;
	}
	if (!one[i])
		return (1);
	else
		return (2);
}

static void	delete_head_from_env(t_list **dup_env, t_env **line, t_list **tmp)
{
	t_env	*caster;

	caster = (t_env *)((*tmp)->content);
	if (ft_lstsize(*dup_env) == 1)
	{
		(*line) = duplicate_env_line(caster);
		ft_lstclear(dup_env, empty_env_element);
	}
	else if ((*line) == (*dup_env)->content)
	{
		(*line) = duplicate_env_line(*line);
		t_list *hello = (*dup_env)->next;
		ft_lstdelone((*dup_env), empty_env_element);
		*dup_env = hello;
	}
}

static t_env	*first_var_in_ascii(t_list **env)
{
	t_env	*line;
	t_list	*tmp;
	t_list	*first;
	t_list	*previous;

	line = (*env)->content;
	tmp = (*env);
	first = tmp;
	previous = NULL;
	while (tmp && tmp->next)
	{
		if (comes_first_in_ascii(line->variable,
				((t_env *)(tmp->next->content))->variable) == 2)
		{
			first = tmp->next;
			line = (t_env *)(first->content);
			previous = tmp;
		}
		tmp = tmp->next;
	}
	if (!previous)
		delete_head_from_env(env, &line, &tmp);
	else
		delete_element_from_list(&previous, &first, &line);
	return (line);
}

static void	print_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s", ((t_env *)tmp->content)->variable);
		if (((t_env *)(tmp->content))->value)
			printf("=\"%s\"\n", ((t_env *)tmp->content)->value);
		else
			printf("\n");
		tmp = tmp->next;
	}
}

void	print_env_in_ascii_order(t_list *env)
{
	t_list	*duplicated_env;
	t_list	*sorted_env;
	int		env_size;

	duplicated_env = duplicate_list(env);
	sorted_env = NULL;
	env_size = ft_lstsize(duplicated_env);
	//env_size = ft_lstsize(env);
	// printf("\n\n\nprinting env\n\n\n");
	// print_env(env);
	while (ft_lstsize(sorted_env) != env_size)
	{
		//printf("%d Call : sorted env\n", p++);
		ft_lstadd_back(&sorted_env,
			ft_lstnew(first_var_in_ascii(&duplicated_env)));
		
	}
	//t_list *test = sorted_env;
	/*while (test) {
		printf("%s...\n", ((t_env *)(test->content))->variable);
		test = test->next;
	}*/
	//ft_lstsiize(sorted_env);
	// printf("\n\n\nprinting sorted env\n\n\n");
	print_env(sorted_env);
	free_env(&duplicated_env);
	free_env(&sorted_env);
}
