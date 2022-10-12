/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:19 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/10 11:35:35 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenlen(t_token *token_list)
{
	t_token	*temp;
	int		count;

	temp = token_list;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
