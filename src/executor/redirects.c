/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:20:25 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/26 14:47:31 by pniezen       ########   odam.nl         */
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
	char	*msg;

	if (access(token->content, F_OK | R_OK | W_OK) == -1)
	{
		msg = ft_strjoin(token->content, ": ");
		return (err_msg(msg, strerror(errno), NULL),
			set_exit_code(errno), exit(1));
	}
	if (rd->fd_in != STDIN_FILENO)
		close(rd->fd_in);
	rd->fd_in = open(token->content, O_RDWR, 0777);
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
static void	set_outfile(t_token *token, t_redirect *rd, bool append)
{
	char	*msg;

	if (rd->fd_out != STDOUT_FILENO)
		close(rd->fd_out);
	if (append == true)
		rd->fd_out = open(token->content, O_APPEND | O_WRONLY | O_CREAT, 0777);
	else if (append == false)
		rd->fd_out = open(token->content, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (rd->fd_out == -1)
	{
		msg = ft_strjoin(token->content, ": ");
		return (err_msg(msg, strerror(errno), NULL),
			set_exit_code(errno), exit(1));
	}
	rd->redirects_count++;
}

/**
 * @brief Creates a array of strings. Each string is a delimiter.
 * (I think a 'heredoc stopping word' is called a delimiter.) This function
 * only sets the delimiters. It does not yet start the heredoc append mode.
 * @param token_list Pointer to the first token of the token_list
 * @param rd Pointer to the redirect struct
 * @return Nothing
 * @note The heredoc_words array does not get new pointers/strings assigned to
 * it. It uses pointers to certain tokens that are already in the token_list.
 */
static void	set_heredoc(t_token *token_list, t_redirect *rd)
{
	t_token	*token;
	int		i;

	i = 0;
	token = token_list;
	if (rd->heredoc_count == 0)
	{
		rd->heredoc_words = NULL;
		return ;
	}
	rd->heredoc_words = ft_calloc(rd->heredoc_count, sizeof(char *));
	while (token && token->type != is_pipe)
	{
		if (token->previous && token->previous->type == delimiter)
			rd->heredoc_words[i++] = token->content;
		token = token->next;
	}
}

/**
 * @brief Sets all values inside the redirect struct.
 * @param rd Pointer to the redirect struct
 * @return Nothing
 * @note
 */
static void	set_redirect_starting_values(t_redirect *rd)
{
	rd->fd_in = 0;
	rd->fd_out = 1;
	rd->id_last_in = -1;
	rd->redirects_count = 0;
	rd->arg_count = 0;
	rd->arg_str = NULL;
	rd->heredoc_count = 0;
	rd->heredoc_words = NULL;
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
		else if (token->type == outfile
			&& token->previous->type == redirect_output)
			set_outfile(token, rd, false);
		else if (token->type == outfile
			&& token->previous->type == redirect_output_append)
			set_outfile(token, rd, true);
		else if (token->previous && token->previous->type == delimiter)
			rd->heredoc_count++;
		else if (token->type != redirect_input
			&& token->type != redirect_output && token->type != delimiter
			&& token->type != redirect_output_append)
			rd->arg_count++;
		token = token->next;
	}
	set_heredoc(token_list, rd);
	create_arg_array_str(token_list, rd);
}
