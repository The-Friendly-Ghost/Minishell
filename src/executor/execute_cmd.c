/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/01 10:50:09 by pniezen       ########   odam.nl         */
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

/**
 * @brief Checks what type of builtin has to be executed. After that, a builtin
 * function gets called that executes the builtin.
 * @param type The type of the current token
 * @param token_list A pointer to the first token of the token list
 * @param argv Array of environment variables
 * @return Nothing
 * @note
 */
static void	exec_builtin(t_token_type type, t_token *token_list, char **argv)
{
	char	*char_exit_code;

	char_exit_code = ft_itoa(get_program()->exit_code);
	if (type == print_exit_code)
		return (err_msg(char_exit_code, ": command not found", NULL),
			set_exit_code(127), free(char_exit_code));
	set_exit_code(0);
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
	if (type == invalid_input)
		return (err_msg(token_list->content, ": command not found", NULL));
	if (type == exit_program)
		return (exit_minishell(token_list));
}

/**
 * @brief Changes STDOUT and STDIN to another file descriptor if there is an
 * outfile or infile in the command line.
 * @param rd Struct with redirect information in it
 * @return Nothing
 */
static void	set_dup(t_redirect *rd)
{
	dup2(rd->fd_in, STDIN_FILENO);
	if (rd->fd_in != STDIN_FILENO)
		close(rd->fd_in);
	dup2(rd->fd_out, STDOUT_FILENO);
	if (rd->fd_out != STDOUT_FILENO)
		close(rd->fd_out);
	return ;
}

void	exec_command(t_token *token_list, t_token_type type, char **argv)
{
	pid_t		fork_pid;
	char		*cmd_path;
	char		**env_array;
	t_redirect	rd;
	int			child_state;

	signal(SIGINT, executor_signal_handler);
	signal(SIGQUIT, executor_signal_handler);
	if (type >= print_exit_code)
		return (exec_builtin(type, token_list, argv));
	set_exit_code(0);
	fork_pid = fork();
	if (fork_pid == -1)
		return ;
	else if (fork_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		check_redirect(token_list, &rd);
		set_dup(&rd);
		env_array = get_env_array();
		if (!env_array)
			exit(127);
		cmd_path = get_executable_path(token_list->content);
		if (!cmd_path)
			return (free(cmd_path),
				destroy_double_array(env_array), exit(errno));
		// for (int i = 0; rd.arg_str[i]; i++)
		// 	printf("[%s]\n", rd.arg_str[i]);
		execve(cmd_path, rd.arg_str, env_array);
		destroy_double_array(env_array);
		exit(errno);
	}
	waitpid(fork_pid, &child_state, WUNTRACED);
	return (set_exit_code(WEXITSTATUS(child_state)));
}
