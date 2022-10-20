/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:20:25 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/20 10:39:10 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <fcntl.h>

static int	check_set_infile(char *token)
{
	if (access(token, F_OK | R_OK | W_OK) == -1)
		return ((void)printf(
				"minishell: %s: %s\n",
				token, strerror(errno)), set_exit_code(errno), 0);
	return (0);
}

static int	check_set_outfile(char *token, int current_fd)
{
	int	new_fd;

	if (current_fd != STDOUT_FILENO)
		close(current_fd);
	new_fd = open(token, O_CREAT | O_RDWR);
	if (new_fd == -1)
		return ((void)printf(
				"minishell: %s: %s\n",
				token, strerror(errno)), set_exit_code(errno), 0);
	return (new_fd);
}

int	check_redirect(t_token *token_list, t_redirect *redirect)
{
	t_token	*temp;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	temp = token_list;
	while (temp && temp->type != is_pipe)
	{
		if (temp->type == infile)
			redirect->fd_in = check_set_infile(temp->content);
		else if (temp->type == outfile)
			redirect->fd_out = check_set_outfile(temp->content, fd_out);
		else if (temp->type == redirect_output_append)
			return (1);
		temp = temp->next;
	}
	return (1);
}
