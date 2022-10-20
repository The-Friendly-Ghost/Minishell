/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/20 13:19:28 by cpost         ########   odam.nl         */
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

static void	exec_builtin(t_token_type type, t_token *token_list,
		char **argv, int *count)
{
	if (type == print_exit_code)
	{
		if (*count > 0)
			return ((void)printf("minishell: 127: command not found\n"));
		(*count)++;
		printf("minishell: %i: command not found\n",
			get_program()->exit_code);
	}
	else if (type == echo)
		return (*count = 0, echo_builtin(token_list));
	else if (type == cd)
		return (*count = 0, cd_builtin(token_list));
	else if (type == pwd)
		return (*count = 0, print_pwd());
	else if (type == export_var)
		return (*count = 0, export_loop(token_list));
	else if (type == unset)
		return (*count = 0, unset_env_var(argv));
	else if (type == env)
		return (*count = 0, print_env());
}

static void	set_dup(t_redirect *redirect)
{
	dup2(redirect->fd_in, STDIN_FILENO);
	close(redirect->fd_in);
	dup2(redirect->fd_out, STDOUT_FILENO);
	close(redirect->fd_out);
	return ;
}

void	exec_command(t_token *token_list, t_token_type type, char **argv)
{
	static int	count;
	pid_t		fork_pid;
	char		*cmd_path;
	char		**env_array;
	t_redirect	redirect;
	char		*dinges[] = {"cat", "Makefile", NULL};

	redirect.fd_in = 0;
	redirect.fd_out = 1;
	if (type >= print_exit_code)
		return (exec_builtin(type, token_list, argv, &count));
	if (!check_redirect(token_list, &redirect))
		return ;
	fork_pid = fork();
	if (fork_pid == -1)
		return ;
	else if (fork_pid == 0)
	{
		set_dup(&redirect);
		env_array = get_env_array();
		if (!env_array)
			exit(1);
		cmd_path = get_executable_path(token_list->content);
		if (!cmd_path)
			return (free(cmd_path));
		execve(cmd_path, dinges, env_array);
		destroy_double_array(env_array);
		exit(errno);
	}
	waitpid(fork_pid, NULL, WUNTRACED);
	return (count = 0, set_exit_code(0));
}
