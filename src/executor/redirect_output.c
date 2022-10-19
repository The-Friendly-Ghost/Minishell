/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_output.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 14:32:26 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/18 17:28:21 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

/**
 * @brief  
 * @param token_list 
 * @param fd
 * @return An integer to a file descriptor.
 * @note
 */
static int	set_output_file(t_token *token_list, int current_fd)
{
	int	new_fd;

	close(current_fd);
	new_fd = open(token_list->content, O_RDONLY | O_CREAT);
	if (new_fd == -1)
	{
		set_exit_code(errno);
		//GEEF ERROR MESSAGE EN RETURN
	}
	return (new_fd);
}

/**
 * @brief  
 * @param token_list 
 * @return An integer to a file descriptor. If no output redirects are found,
 * the return value is that of STDOUT (1). Otherwise it's the value of the
 * file where the output has to be stored.
 * @note
 */
void	check_redirect_output(t_token *token_list)
{
	t_token	*temp;
	int		fd;

	fd = STDOUT_FILENO;
	temp = token_list;
	while (temp && temp->type != is_pipe)
	{
		if (temp->type == redirect_output)
		{
			if (temp->next)
				fd = set_output_file(temp->next, fd);
			//else
				//SYNTAX ERROR 'expected newline ....'
		}
		temp = temp->next;
	}
	if (fd != STDOUT_FILENO)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
