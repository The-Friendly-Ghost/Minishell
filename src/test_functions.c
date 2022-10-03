

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 16:01:09 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/24 16:12:11 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	while (temp)
	{
		printf("id = %d - type = %d : %s\n", temp->id, temp->type, temp->content);
		temp = temp->next;
	}
}