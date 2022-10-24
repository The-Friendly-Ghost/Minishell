/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:13:37 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/24 11:56:32 by pniezen       ########   odam.nl         */
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
	t_env		**env;
	t_env		*temp;

	env = get_env_list();
	if (!(*env))
		return (set_exit_code(127));
	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(temp->var_name, "PATH") && temp->unset)
			return (set_exit_code(127),
				(void)printf("minishel: env: No such file or directory\n"));
		temp = temp->next;
	}
	temp = *env;
	while (temp)
	{
		if (temp->has_value == true && temp->unset == false)
			printf("%s=%s\n", temp->var_name, temp->value);
		temp = temp->next;
	}
	set_exit_code(0);
}
