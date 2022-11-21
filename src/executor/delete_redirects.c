/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_redirects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 12:44:23 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/18 12:53:18 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_redirects_from_list2(t_token *temp)
{
	t_token	*temp_next;
	t_token	*temp_prev;

	while (temp)
	{
		temp_prev = temp->previous;
		temp_next = temp->next;
		if (temp->type >= redirect_input && temp->type <= is_heredoc)
		{
			if (temp_prev)
				temp_prev->next = temp_next;
			if (temp_next)
				temp_next->previous = temp_prev;
			free(temp);
		}
		temp = temp_next;
	}
}

t_token	*delete_redirects_from_list(t_token *token_list)
{
	t_token	*temp_next;
	t_token	*temp;
	t_token	*return_tok;

	temp = token_list;
	while (temp && temp->type >= redirect_input && temp->type <= is_heredoc)
	{
		temp_next = temp->next;
		if (temp_next)
			temp_next->previous = NULL;
		free(temp->content);
		free(temp->heredoc_file);
		free(temp);
		temp = temp_next;
	}
	return_tok = temp;
	delete_redirects_from_list2(temp);
	return (return_tok);
}
