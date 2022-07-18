/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:24:41 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/18 14:19:29 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	empty_env_element(void *element)
{
	// t_env	*_element;

	// _element = (t_env *)element;
	// printf("freeing %s\n", _element->variable);
	free(((t_env *)element)->variable);
	if (((t_env *)element)->value)
		free(((t_env *)element)->value);
	free(element);
}

void	free_env(t_list **list)
{
	ft_lstclear(list, &empty_env_element);
}

void	ft_free_list(t_list **liste)
{
	t_list	*temp;

	while (*liste)
	{
		temp = *liste;
		*liste = (*liste)->next;
		free(temp);
	}
	liste = NULL;
}

void	empty_lexer_element(void *element)
{
	
	free(((t_lexer *)(element))->text);
	free((t_lexer *)(element));
}

void	free_lexer(t_list **lexer)
{
	t_list	*tmp;

	tmp = NULL;
	while (*lexer)
	{
		free(((t_lexer *)((*lexer)->content))->text);
		free((t_lexer *)((*lexer)->content));
		tmp = *lexer;
		*lexer = (*lexer)->next;
		free(tmp);
	}
}

void	free_exec_structs(t_exec **struc)
{
	int	i;

	i = 0;
	while (i < ((*struc)->pipes + 1))
	{
		if (((*struc)->commands)[i].args)
			free_tab(((*struc)->commands)[i].args);
		if (((*struc)->commands)[i].command)
			free(((*struc)->commands)[i].command);
		if (((*struc)->commands)[i].hd_delimiter)
			free(((*struc)->commands)[i].hd_delimiter);
		if (((*struc)->commands)[i].infile)
			free(((*struc)->commands)[i].infile);
		if (((*struc)->commands)[i].outfile)
			free(((*struc)->commands)[i].outfile);
		// free(&((*struc)->commands)[i]);
		i++;
	}
	// free((*struc)->commands);
	free(*struc);
}
