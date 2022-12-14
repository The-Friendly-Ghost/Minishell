/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_command_amount.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:07:45 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/21 13:22:49 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

/**
 * @brief Literally like the functions name says.
 * @param token_list - Pointer to the first element of the linked list
 * @return Nothing
 * @note
 */
bool	set_amount_of_commands(t_token **token_list)
{
	t_program	*program;
	t_token		*temp;

	temp = *token_list;
	program = get_program();
	program->amount_commands = 1;
	while (temp)
	{
		if (temp->type == is_pipe)
			program->amount_commands++;
		temp = temp->next;
	}
	if (program->amount_commands > OPEN_MAX)
	{
		err_msg("fork: Resource temporarily unavailable", NULL, NULL);
		set_exit_code(1);
		return (false);
	}
	return (true);
}
