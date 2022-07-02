#include "../minishell.h"

void	ft_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	printf("%s\n", current_dir);
	free(current_dir);
}
