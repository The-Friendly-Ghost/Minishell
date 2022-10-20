/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:20:25 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/19 14:53:16 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static void	check_set_infile(char *token)
{
	if (access(token, F_OK | R_OK | W_OK) == -1)
		return ((void)printf(
				"minishell: %s: %s\n",
				token, strerror(errno)), set_exit_code(errno));
}

int	check_redirect(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp && temp->type != is_pipe)
	{
		if (temp->type == infile)
			check_set_infile(temp->content);
		else if (temp->type == redirect_output)
			return (1);
		else if (temp->type == redirect_output_append)
			return (1);
		temp = temp->next;
	}
	return (1);
}
