#include "../minishell.h"

static t_lexer	*new_token(int token, char *str)
{
	t_lexer	*new_entry;

	new_entry = malloc(sizeof(t_lexer));
	new_entry->token = token;
	new_entry->text = str;
	return (new_entry);
}

t_list	*new_entry_with_token(int token, char *str)
{
	t_lexer	*token_element;
	t_list	*new_entry;

	token_element = new_token(token, str);
	new_entry = ft_lstnew(token_element);
	return (new_entry);
}

void	update_lexer_list(t_list **list, char *text, int token)
{
	t_lexer	*new_entry;

	new_entry = malloc(sizeof(t_lexer));

	new_entry->token = token;
	new_entry->text = text;
	ft_lstadd_back(list, ft_lstnew(new_entry));
}
