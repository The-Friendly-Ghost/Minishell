/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_env_var.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 15:15:31 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/24 14:26:08 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_values(t_env *temp, char *new_value, bool export)
{
	if (export)
	{
		if (!ft_strcmp(temp->var_name, "PATH"))
		{
			temp->unset = false;
			temp->export_unset = true;
			temp->has_value = true;
		}
		temp->export_unset = true;
	}
	else
	{
		if (new_value == NULL)
			temp->has_value = false;
		else
			temp->has_value = true;
	}
}

/**
 * @brief Changes the value of an environment variable. 
 * @param var_name The name of the environment variable that has to be changed
 * @param new_value The new value that 'var_name' has to be changed to
 * @return True if 'var_name' was succesfully changed to the new value. False
 * if 'var_name' was not found.
 * @note Note that 'new_value' and 'var_name' do not get freed in case 'var_name'
 * was not found. This is because sometimes it might be neccessary
 * to retain a certain pointer. If pointers have to be freed, it has to be done
 * in another function.
 */
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
			if (temp->value)
				free(temp->value);
			temp->value = new_value;
			set_values(temp, new_value, export);
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}
