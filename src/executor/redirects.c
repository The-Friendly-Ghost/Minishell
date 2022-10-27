/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:20:25 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/27 14:57:58 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <fcntl.h>

/**
 * @brief Checks if a (in)file exists. (If not, an error is returned.) If the
 * file exists, this file is then set to the redirect struct (rd) as fd_in.
 * @param token A pointer to a specific token
 * @param rd Pointer to the redirect struct
 * @return Nothing
 * @note This function does not yet replace the STDIN for the infile. This is
 * done in another function (with dup2).
 */
static void	set_infile(t_token *token, t_redirect *rd)
{
	if (access(token->content, F_OK | R_OK | W_OK) == -1)
		return ((void)printf(
				"minishell: %s: %s\n",
				token->content, strerror(errno)), set_exit_code(errno));
	if (rd->fd_in != STDIN_FILENO)
		close(rd->fd_in);
	rd->fd_in = open(token->content, O_RDONLY, 0777);
	rd->id_last_in = token->id;
	rd->redirects_count++;
}

/**
 * @brief Checks if a (out)file exists. If not, a new file is created.
 * This existing or newly created file is then set to the redirect struct (rd)
 * as the new fd_out (outfile).
 * @param token A pointer to a specific token
 * @param rd Pointer to the redirect struct
 * @return Nothing
 * @note This function does not yet replace the STDOUT for the outfile. This is
 * done in another function (with dup2).
 */
static void	set_outfile(t_token *token, t_redirect *rd, t_token_type type)
{
	if (rd->fd_out != STDOUT_FILENO)
		close(rd->fd_out);
	if (type == redirect_output_append)
		rd->fd_out = open(token->content, O_APPEND | O_WRONLY | O_CREAT, 0777);
	else if (type == redirect_output)
		rd->fd_out = open(token->content, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (rd->fd_out == -1)
		return ((void)printf(
				"minishell: %s: %s\n",
				token->content, strerror(errno)), set_exit_code(errno));
	rd->redirects_count++;
}

/**
 * @brief Checks for redirects. If redirects are found, other functions
 * are called that will handle the redirects.
 * @param token_list A pointer to the first token of the token list
 * @param rd Pointer to the redirect struct
 * @return Nothing
 * @note
 */
void	check_redirect(t_token *token_list, t_redirect *rd)
{
	t_token	*token;

	token = token_list;
	set_redirect_starting_values(rd);
	while (token && token->type != is_pipe)
	{
		if (token->type == infile)
			set_infile(token, rd);
		else if (token->type == outfile)
			set_outfile(token, rd, token->previous->type);
		else if (token->type != redirect_input
			&& token->type != redirect_output && token->type != delimiter
			&& token->type != redirect_output_append)
			rd->arg_count++;
		token = token->next;
	}
	create_arg_array_str(token_list, rd);
}
