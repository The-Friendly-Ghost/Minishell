/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_env_var.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 15:15:31 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/13 10:45:38 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	change_env_var(char *var_name, char *new_value, bool export)
{
	t_env	**env_list;
	t_env	*temp;

	env_list = get_env_list();
	temp = *env_list;
	while (temp)
	{
		if (!ft_strcmp(temp->var_name, var_name))
		{
			printf("%s, %s\n", temp->var_name, var_name);
			free(temp->value);
			temp->value = new_value;
			if (export)
				temp->has_value = true;
			else
			{
				if (new_value == NULL)
					temp->has_value = false;
				else
					temp->has_value = true;
			}
			return (true);
		}
		temp = temp->next;
	}
	printf("false\n");
	return (false);
}
