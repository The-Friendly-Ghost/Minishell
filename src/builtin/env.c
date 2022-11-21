/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:13:37 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/21 12:24:21 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_error_check(t_env *temp, char *path)
{
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
}

/**
 * @brief Prints all environment variables
 * @param none
 * @return none
 * @note
 */
void	print_env(void)
{
	t_env		**env;
	t_env		*temp;

	env = get_env_list();
	if (!(*env))
		return (set_exit_code(127));
	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(temp->var_name, "PATH"))
			env_error_check(temp, temp->value);
		temp = temp->next;
	}
	temp = *env;
	while (temp)
	{
		if (temp->has_value && !temp->unset)
			printf("%s=%s\n", temp->var_name, temp->value);
		else if (!temp->has_value && temp->export_unset)
			printf("%s=\n", temp->var_name);
		temp = temp->next;
	}
}
