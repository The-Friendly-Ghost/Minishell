/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 11:10:19 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/08 14:30:45 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_std_and_set_signals(void)
{
	t_program	*program;

	signal(SIGINT, executor_signal_handler);
	signal(SIGQUIT, executor_signal_handler);
	set_exit_code(0);
	program = get_program();
	program->std_backup[0] = dup(STDIN_FILENO);
	if (program->std_backup[0] == -1)
		return (err_msg(NULL, NULL, NULL), set_exit_code(1));
	program->std_backup[1] = dup(STDOUT_FILENO);
	if (program->std_backup[1] == -1)
		return (err_msg(NULL, NULL, NULL), set_exit_code(1));
//err_msg bij beide dups veranderen!
}

void	restore_std(void)
{
	t_program	*program;

	program = get_program();
	if (dup2(program->std_backup[0], STDIN_FILENO) == -1)
		return (err_msg(NULL, NULL, NULL), set_exit_code(1));
	if (dup2(program->std_backup[1], STDOUT_FILENO) == -1)
		return (err_msg(NULL, NULL, NULL), set_exit_code(1));
//err_msg bij beide dup2 veranderen!
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
		if (temp == NULL)
			return (free(temp_prev), NULL);
		if (temp_prev->type == is_pipe)
		{
			free(temp_prev);
			temp->previous = NULL;
			return (temp);
		}
		free(temp_prev);
	}
}
