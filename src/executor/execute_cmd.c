/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/06 14:49:22 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>

static void	exec_builtin(int type, char **argv)
{
	if (type == echo)
		echo_builtin(argv);
	else if (type == pwd)
		print_pwd();
}

int	exec_command(int type, char **argv, char **envp)
{
	pid_t	pid;
	char	*cmd_path;
	int		return_execute;

	cmd_path = get_executable_path(argv[0]);
	if (!cmd_path)
		return (free(cmd_path), -1);
	if (type >= echo)
		return (exec_builtin(type, argv), 0);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		return_execute = execve(cmd_path, argv, envp);
		if (return_execute == -1)
			exit (errno);
		return (0);
	}
	waitpid(pid, NULL, WUNTRACED);
	return (0);
}
