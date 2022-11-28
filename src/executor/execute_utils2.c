/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 13:53:23 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/28 14:47:35 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	set_pipes(int ends[2], t_token *token_list)
{
	close(ends[READ_END]);
	if (is_last_command(token_list) == false)
		dup2(ends[WRITE_END], STDOUT_FILENO);
	close(ends[WRITE_END]);
}

pid_t	ft_get_a_pid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exit(0);
	return (pid);
}

void	wait_processes(pid_t pid, bool child)
{
	int	child_state;

	child_state = 0;
	waitpid(pid, &child_state, WUNTRACED);
	while (wait(NULL) > 0)
		continue ;
	if (WTERMSIG(child_state) == SIGINT)
		ft_putendl_fd("^C", 1);
	else if (WTERMSIG(child_state) == SIGQUIT)
		ft_putendl_fd("^\\Quit: 3", 1);
	else if (WIFSIGNALED(child_state))
		set_exit_code(WTERMSIG(child_state) + 128);
	else if (WIFEXITED(child_state) && child)
		set_exit_code(WEXITSTATUS(child_state));
}

bool	cmd_is_builtin(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp && temp->type != is_pipe)
	{
		if ((temp->type >= redirect_input && temp->type <= is_heredoc)
			|| !ft_strcmp(temp->content, ""))
			temp = temp->next;
		else if (temp->type >= print_exit_code)
			return (true);
		else
			return (false);
	}
	return (false);
}
