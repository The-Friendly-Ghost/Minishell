/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:20:25 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/28 14:29:57 by pniezen       ########   odam.nl         */
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
static bool	set_infile(t_token *token, t_redirect *rd)
{
	char	*msg;

	if (access(trim_quotes(token->content), F_OK | R_OK | W_OK) == -1)
	{
		msg = ft_strjoin(token->content, ": ");
		return (err_msg(msg, strerror(errno), NULL),
			set_exit_code(1), free(msg), false);
	}
	if (rd->fd_in != STDIN_FILENO)
		close(rd->fd_in);
	rd->fd_in = open(token->content, O_RDONLY, 0777);
	rd->id_last_in = token->id;
	rd->redirects_count++;
	return (true);
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
	char	*msg;

	if (rd->fd_out != -2)
		close(rd->fd_out);
	if (type == redirect_output_append)
	{
		trim_quotes(token->content);
		rd->fd_out = open(token->content, O_APPEND | O_WRONLY | O_CREAT, 0777);
	}
	else if (type == redirect_output)
	{
		trim_quotes(token->content);
		rd->fd_out = open(token->content, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	}
	if (rd->fd_out == -1)
	{
		msg = ft_strjoin(token->content, ": ");
		return (err_msg(msg, strerror(errno), NULL),
			free(msg), set_exit_code(errno));
	}
	rd->redirects_count++;
}

/**
 * @brief Creates a array of strings with all irrelevant redirects removed from
 * it. Each string is an argument that will be passed on the execve.
 * @param token_list Pointer to the first token of the token_list
 * @param rd Pointer to the redirect struct
 * @return Nothing
 * @note The rd->arg_arr get malloced, but the strings inside do not get
 * malloced. It uses pointers to token->content. These pointers already 
 * exist in the token list.
 */
static void	create_arg_array_str(t_token *token_list, t_redirect *rd,
	t_token *temp, int i)
{
	char	*removed_quotes;

	i = 0;
	temp = token_list;
	rd->arg_arr = ft_nulloc(rd->arg_count + rd->redirects_count + 1);
	if (!rd->arg_arr)
		return ;
	while (temp && temp->type != is_pipe)
	{
		if (temp->content && temp->content[0] == '\'')
			removed_quotes = ft_strtrim(temp->content, "\'");
		else if (temp->content && temp->content[0] == '\"')
			removed_quotes = ft_strtrim(temp->content, "\"");
		else
			removed_quotes = ft_strdup(temp->content);
		if (!removed_quotes)
			return (err_msg(NULL, NULL, NULL));
		if ((rd->arg_count <= 1 && temp->id == rd->id_last_in
				&& !ft_strcmp(token_list->content, "cat"))
			|| (temp->type < redirect_input || temp->type > is_heredoc))
			rd->arg_arr[i++] = removed_quotes;
		else
			free(removed_quotes);
		temp = temp->next;
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
	rd->arg_arr = NULL;
	rd->fd_in = 0;
	rd->fd_out = -2;
	rd->id_last_in = -1;
	rd->redirects_count = 0;
	rd->arg_count = 0;
}

/**
 * @brief Checks for redirects. If redirects are found, other functions
 * are called that will handle the redirects.
 * @param token_list A pointer to the first token of the token list
 * @param rd Pointer to the redirect struct
 * @return Nothing
 * @note
 */
bool	check_redirect(t_token *token_list, t_redirect *rd)
{
	t_token	*token;

	token = token_list;
	set_redirect_starting_values(rd);
	while (token && token->type != is_pipe)
	{
		if (token->type == infile)
		{
			if (!set_infile(token, rd))
				return (false);
		}
		else if (token->type == outfile)
			set_outfile(token, rd, token->previous->type);
		else if (token->type != redirect_input
			&& token->type != redirect_output && token->type != delimiter
			&& token->type != redirect_output_append)
			rd->arg_count++;
		token = token->next;
	}
	create_arg_array_str(token_list, rd, NULL, 0);
	set_dup(rd);
	return (true);
}
