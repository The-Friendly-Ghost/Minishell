/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 15:06:33 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/02 14:52:35 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_env *curr, char *str)
{
	t_env	*prev;
	t_env	*temp;

	while (curr && curr->next)
	{
		if (ft_strcmp(curr->var_name, str) == 0)
		{
			printf("%s == %s\n", curr->var_name, str);
			temp = curr->next;
			prev = curr->previous;
			prev->next = temp;
			temp->previous = prev;
			free(curr);
			break ;
		}
		else
			curr = curr->next;
	}
}

void	unset_env_var(char **argv)
{
	t_env	**env_list;
	t_env	*curr;
	int		i;

	if (!argv[1])
		return ;
	i = 1;
	env_list = get_env_list();
	while (*env_list && ft_strcmp((*env_list)->var_name, argv[i]) == 0)
	{
		curr = *env_list;
		*env_list = (*env_list)->next;
		(*env_list)->previous = NULL;
		free(curr);
	}
	while (argv[i])
	{
		curr = *env_list;
		delete_node(curr, argv[i]);
		i++;
	}
}
