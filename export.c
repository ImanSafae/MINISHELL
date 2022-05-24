#include "minishell.h"

t_env	*first_in_ascii(t_list **env)
{
	t_env	*line;
	t_list	*tmp;
	t_list	*new_next;

	line = (*env)->content;
	tmp = (*env);
	new_next = NULL;
	while (tmp && tmp->next)
	{
		if ((line->variable)[0] > (((t_env *)(tmp->next->content))->variable)[0])
		{
			line = tmp->next->content;
			new_next = tmp->next->next;
			ft_lstdelone(tmp->next, delete_element);
			tmp->next = new_next;
		}
		tmp = tmp->next;
	}
	if (!(*env)->next)
	{
		ft_lstdelone(tmp, delete_element);
	}
	// print_env(env);
	return (line);
}

t_list	*recreate_sorted_env(t_list *env)
{
	t_list *duplicated_env;
	t_list	*sorted_env;

	duplicated_env = env;
	sorted_env = ft_lstnew(first_in_ascii(&duplicated_env));
	while (duplicated_env)
	{
		ft_lstadd_back(&sorted_env, ft_lstnew(first_in_ascii(&duplicated_env)));
	}
	print_env(&sorted_env);
	return (sorted_env);
}

void	print_env_in_ascii_order(t_list *env)
{
	t_list	*sorted_env;
	t_list	*tmp;

	printf("test\n");
	sorted_env = recreate_sorted_env(env);
	tmp = sorted_env;
	while (tmp)
	{
		printf("%s=\n", ((t_env *)(tmp->content))->variable);
		printf("%s\n", ((t_env *)(tmp->content))->value);
		tmp = tmp->next;
	}
}

// void	ft_export(t_list **env, char *var)
// {
// 	if (!var)
// 		print_env_ascii(*env);
// }
