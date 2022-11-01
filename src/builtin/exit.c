/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:42:20 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/01 10:42:21 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * @param token_list the linked list with the tokens in it
 * @return 
 * @note
 */
void	exit_minishell(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	if (temp->next == NULL)
		exit(127);
	else if (temp->next && temp->next->content && temp->next->next
		&& temp->next->next->content)
	{
		ft_putendl_fd("exit", 2);
		err_msg("exit: ", "too many arguments", NULL);
		set_exit_code(1);
	}
	else if (temp->next && temp->next->content
		&& !str_is_num(temp->next->content))
	{
		ft_putendl_fd("exit", 2);
		err_msg("exit: ", temp->next->content, ": numeric argument required");
		exit(255);
	}
	else if (temp->next && temp->next->content
		&& str_is_num(temp->next->content))
	{
		ft_putendl_fd("exit", 1);
		exit(ft_atoi(temp->next->content));
	}
}
