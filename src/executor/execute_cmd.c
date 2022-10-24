/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/24 16:13:53 by pniezen       ########   odam.nl         */
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

static void	exec_builtin(t_token_type type, t_token *token_list, char **argv)
{
	if (type == print_exit_code)
		return ((void)printf("minishell: %i: command not found\n",
				get_program()->exit_code), set_exit_code(127));
	if (type == echo)
		return (echo_builtin(token_list));
	if (type == cd)
		return (cd_builtin(token_list));
	if (type == pwd)
		return (print_pwd());
	if (type == export_var)
		return (export_loop(token_list));
	if (type == unset)
		return (unset_env_var(argv));
	if (type == env)
		return (print_env());
	if (type == 0)
		return ((void)printf("minishell: %s: command not found\n",
				token_list->content));
}

// static void	set_dup(t_redirect *redirect)
// {
// 	dup2(redirect->fd_in, STDIN_FILENO);
// 	close(redirect->fd_in);
// 	dup2(redirect->fd_out, STDOUT_FILENO);
// 	close(redirect->fd_out);
// 	return ;
// }

void	exec_command(t_token *token_list, t_token_type type, char **argv)
{
	t_redirect	redirect;
	pid_t		fork_pid;
	char		*cmd_path;
	char		**env_array;
	t_redirect	rd;

	if (type >= print_exit_code)
		return (exec_builtin(type, token_list, argv));
	fork_pid = fork();
	if (fork_pid == -1)
		return ;
	else if (fork_pid == 0)
	{
		if (!check_redirect(token_list, &rd))
			return ;
		// set_dup(&rd);
		env_array = get_env_array();
		if (!env_array)
			exit(1);
		cmd_path = get_executable_path(token_list->content);
		printf("HIER\n");
		if (!cmd_path)
			return (free(cmd_path));
		execve(cmd_path, rd.arg_str, env_array);
		destroy_double_array(env_array);
		exit(errno);
	}
	waitpid(fork_pid, NULL, WUNTRACED);
	return (set_exit_code(0));
}
