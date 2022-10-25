/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:23:37 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/25 13:19:10 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a array of strings with all irrelevant redirects removed from
 * it. Each string is an argument that will be passed on the execve.
 * @param token_list Pointer to the first token of the token_list
 * @param rd Pointer to the redirect struct
 * @return Nothing
 * @note The rd->arg_str get malloced, but the strings inside do not get
 * malloced. It uses pointers to token->content. These pointers already 
 * exist in the token list.
 */
void	create_arg_array_str(t_token *token_list, t_redirect *rd)
{
	t_token	*token;
	int		i;

	token = token_list;
	i = 0;
	rd->arg_str = ft_nulloc(rd->arg_count + rd->redirects_count + 1);

	if (!rd->arg_str)
		return ;
	while (token && token->type != is_pipe)
	{
		if (token->id == 0)
			rd->arg_str[i++] = ft_strdup(token->content);
		else if (rd->arg_count <= 1 && token->id == rd->id_last_in)
			rd->arg_str[i++] = ft_strdup(token->content);
		else if (token->type < redirect_input || token->type > is_heredoc)
			rd->arg_str[i++] = ft_strdup(token->content);
		token = token->next;
	}
}
