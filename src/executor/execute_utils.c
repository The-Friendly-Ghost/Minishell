/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 11:10:19 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/24 11:18:01 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

/**
 * @brief Changes STDOUT and STDIN to another file descriptor if there is an
 * outfile or infile in the command line.
 * @param rd Struct with redirect information in it
 * @return Nothing
 */
void	set_dup(t_redirect *rd)
{
	dup2(rd->fd_in, STDIN_FILENO);
	if (rd->fd_in != STDIN_FILENO && rd->fd_in >= 0)
		close(rd->fd_in);
	dup2(rd->fd_out, STDOUT_FILENO);
	if (rd->fd_out != STDOUT_FILENO && rd->fd_out >= 0)
		close(rd->fd_out);
	return ;
}

bool	is_last_command(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp)
	{
		if (temp->type == is_pipe)
			return (false);
		temp = temp->next;
	}
	return (true);
}

bool	backup_std_and_set_signals(void)
{
	t_program	*program;

	signal(SIGINT, executor_signal_handler);
	signal(SIGQUIT, executor_signal_handler);
	program = get_program();
	program->std_backup[0] = dup(STDIN_FILENO);
	if (program->std_backup[0] == -1)
		return (set_exit_code(errno), err_msg(strerror(errno), NULL, NULL),
			false);
	program->std_backup[1] = dup(STDOUT_FILENO);
	if (program->std_backup[1] == -1)
		return (set_exit_code(errno), err_msg(strerror(errno), NULL, NULL),
			false);
	return (true);
}

void	restore_std(void)
{
	t_program	*program;

	program = get_program();
	if (dup2(program->std_backup[0], STDIN_FILENO) == -1)
		return (set_exit_code(errno), err_msg(strerror(errno), NULL, NULL));
	if (dup2(program->std_backup[1], STDOUT_FILENO) == -1)
		return (set_exit_code(errno), err_msg(strerror(errno), NULL, NULL));
	close(program->std_backup[0]);
	close(program->std_backup[1]);
}

t_token	*destroy_command(t_token *token_list)
{
	t_token	*temp;
	t_token	*temp_prev;

	temp = token_list;
	while (temp)
	{
		temp_prev = temp;
		temp = temp->next;
		free(temp_prev->content);
		free(temp_prev->heredoc_file);
		if (temp)
			temp->previous = NULL;
		if (temp_prev->type == is_pipe)
			return (free(temp_prev), temp);
		free(temp_prev);
	}
	return (NULL);
}
