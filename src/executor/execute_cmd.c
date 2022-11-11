/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/11 12:28:13 by cpost         ########   odam.nl         */
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
static void	exec_builtin(t_token_type type, t_token *token_list, pid_t *pid)
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
		return (unset_env_var(token_list));
	if (type == env)
		return (print_env());
	if (type == invalid_input)
		return (err_msg(token_list->content, ": command not found", NULL));
	if (type == exit_program)
		return (exit_minishell(token_list, pid));
}

static void	execute_child_process(t_token *token_list, int ends[2],
			t_redirect *rd, pid_t *fork_pid)
{
	char		*cmd_path;
	char		**ev_arr;

	signal(SIGINT, SIG_DFL);
	if (token_list->type >= print_exit_code)
	{
		exec_builtin(token_list->type, token_list, fork_pid);
		close(ends[WRITE_END]);
		printf("ERRNO: %d\n", errno);
		exit(errno);
	}
	ev_arr = get_env_array();
	if (!ev_arr)
		exit(127);
	cmd_path = get_executable_path(token_list->content);
	if (!cmd_path)
		return (destroy_double_array(ev_arr), free(cmd_path), exit(errno));
	execve(cmd_path, rd->arg_str, ev_arr);
	if (!ft_strcmp("./minishell", token_list->content))
		err_msg(token_list->content, ": is a directory", NULL);
	destroy_double_array(ev_arr);
}

void	execute_child(t_token *token_list, pid_t *fork_pid,
			t_redirect *rd)
{
	int			ends[2];

	if (pipe(ends) == -1)
		exit(1);
	*fork_pid = fork();
	if (*fork_pid == -1)
		return ;
	if (*fork_pid == 0)
	{
		set_pipes(ends, token_list);
		check_redirect(token_list, rd);
		execute_child_process(token_list, ends, rd, fork_pid);
		exit(errno);
	}
	close(ends[WRITE_END]);
	dup2(ends[READ_END], STDIN_FILENO);
	close(ends[READ_END]);
}

void	exec_command(t_token **token_list)
{
	pid_t		pid;
	t_redirect	rd;
	int			child_state;

	backup_std_and_set_signals();
	pid = ft_getpid();
	while (*token_list)
	{
		if ((*token_list)->type >= print_exit_code
			&& get_program()->amount_commands == 1)
		{
			check_redirect(*token_list, &rd);
			exec_builtin((*token_list)->type, *token_list, &pid);
			break ;
		}
		execute_child(*token_list, &pid, &rd);
		*token_list = destroy_command(*token_list);
	}
	waitpid(pid, &child_state, WUNTRACED);
	while (wait(NULL) > 0)
		continue ;
	restore_std();
	return (set_exit_code(WEXITSTATUS(child_state)));
}
