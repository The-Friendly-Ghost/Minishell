/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:13:37 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/26 14:54:43 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints all environment variables
 * @param none
 * @return none
 * @note
 */
void	print_env(void)
{
	static char	*path;
	t_env		**env;
	t_env		*temp;

	env = get_env_list();
	if (!(*env))
		return (set_exit_code(127));
	temp = *env;
	while (temp)
	{
		if (!path && !ft_strcmp(temp->var_name, "PATH"))
			path = ft_strdup(temp->value);
		if (!ft_strcmp(temp->var_name, "PATH") && temp->unset)
		{
			if (!temp->value)
				return (set_exit_code(127),
					err_msg("env: ", "No such file or directory", NULL));
		}
		if (!ft_strcmp(temp->var_name, "PATH") && !temp->unset)
		{
			if (ft_strcmp(temp->value, path))
				return (set_exit_code(127),
					err_msg("env: ", "command not found", NULL));
		}
		temp = temp->next;
	}
	temp = *env;
	while (temp)
	{
		if (temp->has_value == true && temp->unset == false)
			printf("%s=%s\n", temp->var_name, temp->value);
		temp = temp->next;
	}
}
