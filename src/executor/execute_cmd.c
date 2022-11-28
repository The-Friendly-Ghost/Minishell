/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:49:16 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/28 11:24:06 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static bool	check_empty_export(t_token *token_list)
{
	t_token	*temp;

	temp = token_list->next;
	while (temp && !ft_strcmp(temp->content, ""))
		temp = temp->next;
	if (!temp || temp->type == is_pipe)
		return (true);
	return (false);
}

static void	export_loop(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	if (check_empty_export(token_list))
		return (print_export_env());
fprintf(stderr, "voor\n");
	while (temp)
	{
		if (temp->next && temp->next->type == is_pipe)
			break ;
		if (temp->next && ft_strcmp(temp->next->content, ""))
			export_env_var(temp);
		temp = temp->next;
	}
fprintf(stderr, "na\n");
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
static void	exec_builtin(t_token_type type, t_token *token_list)
{
	char	*char_exit_code;

	char_exit_code = ft_itoa(get_program()->exit_code);
	if (type == print_exit_code)
		return (err_msg(char_exit_code, ": command not found", NULL),
			set_exit_code(127), free(char_exit_code));
	free(char_exit_code);
	set_exit_code(0);
	if (type == echo)
		return (echo_builtin(token_list, 1));
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
		return (exit_minishell(token_list));
}

static void	execute_child_process(t_token *token_list, int ends[2],
			t_redirect *rd)
{
	char		*cmd_path;
	char		**ev_arr;

	signal(SIGINT, SIG_DFL);
	if (cmd_is_builtin(token_list))
	{
		token_list = delete_redirects_from_list(token_list);
		exec_builtin(token_list->type, token_list);
		close(ends[WRITE_END]);
		exit(get_program()->exit_code);
	}
	ev_arr = get_env_array();
	if (!ev_arr)
		exit(127);
	cmd_path = create_executable_path(token_list);
	if (!cmd_path)
		return (destroy_double_array(ev_arr), free(cmd_path),
			exit(get_program()->exit_code));
	execve(cmd_path, rd->arg_arr, ev_arr);
	err_msg(token_list->content, ": ", strerror(errno));
	destroy_double_array(ev_arr);
}

static bool	execute_child(t_token *token_list, pid_t *fork_pid,
			t_redirect *rd)
{
	int			ends[2];

	if (pipe(ends) == -1)
		exit(1);
	*fork_pid = fork();
	if (*fork_pid == -1)
		return (false);
	if (*fork_pid == 0)
	{
		set_pipes(ends, token_list);
		if (!check_redirect(token_list, rd))
			exit(get_program()->exit_code);
		execute_child_process(token_list, ends, rd);
		exit(127);
	}
	close(ends[WRITE_END]);
	dup2(ends[READ_END], STDIN_FILENO);
	close(ends[READ_END]);
	return (true);
}

void	exec_command(t_token **token_list)
{
	pid_t		pid;
	t_redirect	rd;
	bool		child;

	pid = 0;
	rd.arg_arr = NULL;
	backup_std_and_set_signals();
	while (*token_list)
	{
		if (cmd_is_builtin(*token_list)
			&& get_program()->amount_commands == 1)
		{
			if (check_redirect(*token_list, &rd) == true)
			{
				*token_list = delete_redirects_from_list(*token_list);
				exec_builtin((*token_list)->type, *token_list);
			}
			destroy_double_array(rd.arg_arr);
			break ;
		}
		child = execute_child(*token_list, &pid, &rd);
		*token_list = destroy_command(*token_list);
	}
	return (wait_processes(pid, child), restore_std());
}
