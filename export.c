#include "minishell.h"

static int	comes_first_in_ascii(char *one, char *two)
{
	int	i;

	i = 0;
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

t_env	*first_var_in_ascii(t_list **env)
{
	t_env	*line;
	t_list	*tmp;
	t_list	*first;
	t_list	*previous;

	line = (*env)->content;
	tmp = (*env);
	first = tmp;
	while (tmp && tmp->next)
	{
		if (comes_first_in_ascii(line->variable, ((t_env *)(tmp->next->content))->variable) == 2)
		{
			line = tmp->next->content;
			first = tmp->next;
			previous = tmp;
		}
		tmp = tmp->next;
	}
	if (ft_lstsize((*env)) == 1)
	{
		line = (t_env *)(ft_lstnew(line)->content);
		ft_lstclear(env, delete_element);
	}
	else if (line == (*env)->content)
	{
		line = (t_env *)(ft_lstnew(line)->content);
		tmp = (*env);
		(*env) = (*env)->next;
		ft_lstdelone(tmp, delete_element);
	}
	else
	{
		previous->next = first->next;
		ft_lstdelone(first, delete_element);
	}
	return (line);
}

t_list	*recreate_sorted_env(char **envp)
{
	t_list *duplicated_env;
	t_list	*sorted_env;

	duplicated_env = create_env(envp);
	sorted_env = ft_lstnew(first_var_in_ascii(&duplicated_env));
	while (duplicated_env)
		ft_lstadd_back(&sorted_env, ft_lstnew(first_var_in_ascii(&duplicated_env)));
	return (sorted_env);
}

// void	print_env_in_ascii_order(char **envp)
// {
// 	t_list	*sorted_env;
// 	t_list	*tmp;

// 	sorted_env = recreate_sorted_env(envp);
// 	tmp = sorted_env;
// 	while (tmp)
// 	{
// 		printf("%s=\n", ((t_env *)(tmp->content))->variable);
// 		printf("%s\n", ((t_env *)(tmp->content))->value);
// 		tmp = tmp->next;
// 	}
// }

// void	ft_export(t_list **env, char *var, char **envp)
// {
// 	if (!var)
// 		print_env_in_ascii_order(envp);
// }
