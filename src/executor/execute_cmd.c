/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/13 15:18:47 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>

static void	export_loop(t_token *token_list)
{
	t_token	*temp;
	int		token_len;

	set_exit_code(0);
	token_len = ft_tokenlen(token_list) - 1;
	if (token_len == 0)
		return (print_export_env());
	temp = token_list;
	while (token_len > 0 && temp)
	{
		export_env_var(temp);
		temp = temp->next;
		token_len--;
	}
}

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
		export_loop(token_list);
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
