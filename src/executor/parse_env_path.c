/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:34:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/28 10:03:55 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>

static char	*is_minishell(char *command)
{
	char	*pwd;
	char	*correct_path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (err_msg(NULL, NULL, NULL), NULL);
	correct_path = ft_strjoin(pwd, command);
	free(pwd);
	if (!correct_path)
		return (NULL);
	if (access(correct_path, F_OK | R_OK | X_OK) == 0)
		return (correct_path);
	return (free(correct_path), NULL);
}

static char	*get_correct_path(char *path_line, char *command)
{
	char	**path_list;
	char	*joined;
	char	*correct_path;
	int		i;

	path_list = ft_split(path_line, ':');
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		joined = ft_strjoin(path_list[i], command);
		if (!joined)
			return (destroy_double_array(path_list), NULL);
		if (access(joined, F_OK | X_OK) == 0)
		{
			correct_path = ft_strdup(joined);
			free(joined);
			return (destroy_double_array(path_list), correct_path);
		}
		free(joined);
		i++;
	}
	return (destroy_double_array(path_list), NULL);
}

static char	*check_correct_path(char *path_line, char *command)
{
	char	*correct_path;

	correct_path = is_minishell(command);
	if (correct_path)
		return (correct_path);
	return (get_correct_path(path_line, command));
}

static char	*get_executable_path(char *command_str)
{
	char	*command;
	char	*correct_path;

	if (access(command_str, F_OK | X_OK) == 0)
		return (command_str);
	command = ft_strjoin("/", command_str);
	if (!command)
		return (NULL);
	if (!ft_getenv("PATH"))
		return (set_exit_code(127), free(command),
			err_msg(command_str, ": No such file or directory", NULL), NULL);
	correct_path = check_correct_path(ft_getenv("PATH"), command);
	if (!correct_path)
	{
		set_exit_code(127);
		free(command);
		if (command_str[0] == '/')
			return (err_msg(command_str, ": No such file or directory", NULL),
				NULL);
		return (err_msg(command_str, ": command not found", NULL), NULL);
	}
	return (free(command), correct_path);
}

char	*create_executable_path(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp && temp->type != is_pipe)
	{
		if (temp->type < redirect_input || temp->type > is_heredoc)
		{
			trim_quotes(temp->content);
			if (!temp->content || !ft_strcmp(temp->content, ""))
				return (NULL);
			if (temp->content[0] == '.' && temp->content[1] == '/'
				&& ft_strcmp(temp->content, "./minishell"))
				if (access(temp->content, F_OK | X_OK | AT_FDCWD) == -1)
					return (set_exit_code(127), temp->content);
			return (get_executable_path(temp->content));
		}
		temp = temp->next;
	}
	return (NULL);
}
