/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 15:06:33 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/07 15:30:46 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env_var(char **argv)
{
	t_env	**env_list;
	t_env	*temp;
	int		i;

	env_list = get_env_list();
	i = 1;
	while (argv[i])
	{
		temp = *env_list;
		while (temp)
		{
			if (temp->has_value && !ft_strcmp(temp->var_name, argv[i]))
				temp->unset = true;
			temp = temp->next;
		}
		i++;
	}
	set_exit_code(0);
}
