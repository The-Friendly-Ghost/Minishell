/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 13:53:23 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/16 12:44:36 by pniezen       ########   odam.nl         */
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

pid_t	ft_get_a_pid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exit(0);
	return (pid);
}

t_token	*move_command_in_front(t_token *token_list)
{
	t_token	*temp;
	t_token	*prev;
	t_token	*next;

	temp = token_list;
	if (temp->type < redirect_input || temp->type > is_heredoc)
		return (token_list);
	while (temp && temp->type != is_pipe)
	{
		if (temp->type < redirect_input || temp->type > is_heredoc)
		{
			prev = temp->previous;
			next = temp->next;
			prev->next = next;
			next->previous = prev;
			temp->next = token_list;
			temp->previous = NULL;
			return (temp);
		}
		temp = temp->next;
	}
	destroy_token_list(&token_list);
	return (NULL);
}

void	wait_processes(pid_t pid)
{
	int	child_state;

	child_state = 0;
	waitpid(pid, &child_state, WUNTRACED);
	while (wait(NULL) > 0)
		continue ;
	if (WIFEXITED(child_state) && !WIFSIGNALED(child_state))
		set_exit_code(WEXITSTATUS(child_state));
	if (WIFSIGNALED(child_state) && get_program()->exit_code == 130)
		ft_putendl_fd("^C", 1);
	if (WIFSIGNALED(child_state) && get_program()->exit_code == 131)
		ft_putendl_fd("^\\Quit: 3", 1);
}
