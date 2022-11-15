#include "minishell.h"

void	print_token_list(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp)
	{
		printf("type: %d - [%s]\n", temp->type, temp->content);
		temp = temp->next;
	}
}
