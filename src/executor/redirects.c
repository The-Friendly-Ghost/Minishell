/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:20:25 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/21 16:25:41 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <fcntl.h>

static void	set_infile(t_token *token, t_redirect *rd)
{
	if (access(token->content, F_OK | R_OK | W_OK) == -1)
		return ((void)printf(
				"minishell: %s: %s\n",
				token->content, strerror(errno)), set_exit_code(errno));
	if (rd->fd_in != STDIN_FILENO)
		close(rd->fd_in);
	rd->fd_in = open(token->content, O_RDWR, 0777);
	rd->id_last_in = token->id;
	rd->redirects_count++;
}

static void	set_outfile(t_token *token, t_redirect *rd, bool append)
{
	int	new_fd;

	if (rd->fd_out != STDOUT_FILENO)
		close(rd->fd_out);
	rd->fd_out = open(token->content, O_RDWR | O_CREAT, 0777);
	if (rd->fd_out == -1)
		return ((void)printf(
				"minishell: %s: %s\n",
				token->content, strerror(errno)), set_exit_code(errno));
	rd->append = append;
	rd->redirects_count++;
}


static void	set_heredoc(t_token *token, t_redirect *rd)
{
	
}

static void	set_redirect_starting_values(t_redirect *rd)
{
	rd->fd_in = 0;
	rd->fd_out = 1;
	rd->id_last_in = -1;
	rd->redirects_count = 0;
	rd->arg_count = 0;
	rd->append = false;
	rd->arg_str = NULL;
	rd->heredoc_stop = NULL;
}

int	check_redirect(t_token *token_list, t_redirect *rd)
{
	t_token	*token;

	token = token_list;
	set_redirect_starting_values(rd);
	while (token && token->type != is_pipe)
	{
		if (token->type == infile)
			set_infile(token, rd);
		else if (token->type == outfile
			&& token->previous->type == redirect_output)
			set_outfile(token, rd, false);
		else if (token->type == outfile
			&& token->previous->type == redirect_output_append)
			set_outfile(token, rd, true);
		else if (token->previous && token->previous->type == delimiter)
			set_heredoc(token, rd);
		else if (token->type != redirect_input
			&& token->type != redirect_output)
			rd->arg_count++;
		token = token->next;
	}
	create_arg_array_str(token_list, rd);
	return (1);
}
