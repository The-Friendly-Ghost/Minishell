/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 13:28:45 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/18 13:29:59 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		printf("type: %d - [%s]\n", temp->type, temp->content);
		temp = temp->next;
	}
}
