/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_env_var.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 15:15:31 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/10 13:58:52 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_var(char *var_name, char *new_value)
{
	t_env	**env_list;
	t_env	*temp;

	env_list = get_env_list();
	temp = *env_list;
	while (temp)
	{
		if (!ft_strcmp(temp->var_name, var_name))
		{
			free(temp->value);
			temp->value = ft_strdup(new_value);
			return ;
		}
		temp = temp->next;
	}
}
