/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/10 13:20:25 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>

static void	exec_builtin(int type, t_token *token_list, char **argv)
{
	if (type == print_exit_code)
		printf("%i\n", get_program()->exit_code);
	else if (type == echo)
		echo_builtin(token_list);
	else if (type == cd)
		cd_builtin(token_list);
	else if (type == pwd)
		print_pwd();
	else if (type == export_var)
		printf("Work in progress.\n");
	else if (type == unset)
		unset_env_var(argv);
	else if (type == env)
		print_env();
}

int	exec_command(t_token *token_list, int type, char **argv)
{
	pid_t	fork_pid;
	char	*cmd_path;
	char	**env_array;

	if (type >= print_exit_code)
		return (exec_builtin(type, token_list, argv), 0);
	cmd_path = get_executable_path(argv[0]);
	if (!cmd_path)
		return (free(cmd_path), -1);
	fork_pid = fork();
	if (fork_pid == -1)
		return (-1);
	else if (fork_pid == 0)
	{
		env_array = get_env_array();
		if (!env_array)
			exit(1);
		execve(cmd_path, argv, env_array);
		destroy_double_array(env_array);
		exit(errno);
	}
	waitpid(fork_pid, NULL, WUNTRACED);
	return (0);
}
