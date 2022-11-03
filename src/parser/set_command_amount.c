/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_pipe_amount.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:07:45 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/03 12:05:00 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Literally like the functions name says.
 * @param token_list - Pointer to the first element of the linked list
 * @return Nothing
 * @note
 */
void	set_amount_of_commands(t_token **token_list)
{
	t_program	*program;
	t_token		*temp;

	program = get_program();
	temp = *token_list;
	while (temp)
	{
		if (temp->type == is_pipe)
			program->amount_commands++;
		temp = temp->next;
	}
}
