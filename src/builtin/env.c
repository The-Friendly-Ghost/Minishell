/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:13:37 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/23 13:38:19 by cpost         ########   odam.nl         */
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
		return ;
	else
		temp = *env;
	while (temp)
	{
		if (temp->has_value == true)
			printf("%s=%s\n", temp->var_name, temp->value);
		temp = temp->next;
	}
}
