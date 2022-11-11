/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 13:53:23 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/11 11:08:04 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipes(int ends[2], t_token *token_list)
{
	close(ends[READ_END]);
	if (is_last_command(token_list) == false)
		dup2(ends[WRITE_END], STDOUT_FILENO);
	close(ends[WRITE_END]);
}

pid_t	ft_getpid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exit(0);
	return (pid);
}
