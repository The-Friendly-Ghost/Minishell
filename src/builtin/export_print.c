/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 12:04:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/13 12:04:21 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_env(void)
{
	t_env	**env;
	t_env	*temp;

	env = get_env_list();
	sort_env_list(env);
	if (!(*env))
		return (set_exit_code(127));
	temp = *env;
	while (temp)
	{
		if (!temp->value && !temp->export_unset)
			printf("declare -x %s\n", temp->var_name);
		else
		{
			if (!temp->value && temp->export_unset)
				printf("declare -x %s=\"\"\n", temp->var_name);
			else
				printf("declare -x %s=\"%s\"\n", temp->var_name, temp->value);
		}
		temp = temp->next;
	}
}
