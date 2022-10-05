/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_list_to_array.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 15:14:05 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/05 15:44:41 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_node(t_token *env_var)
{
	
}

/**
 * @brief This function converts the linked list with all the tokens in it to
 * a 2D-array. (This 2D array can be passed as an argument when using execve.)
 * @param nothing
 * @return Pointer to the the 2D array (array filled with env variables)
 * @note -
 */
char	**convert_list_to_array(void)
{
	t_env		**env;
	t_env		*temp;
	char		**env_list;
	int			node;

	node = 0;
	env = get_env_list();
	if (!(*env))
		return (NULL);
	else
		temp = *env;
	while (temp)
	{
		node++;
		temp = temp->next;
	}
	env_list = malloc(sizeof(char *) * (node + 1));
	temp = *env;
	node = 0;
	while (temp)
	{
		env_list[node] = create_node(temp);
		temp = temp->next;
		node++;
	}
	return (env_list);
}
