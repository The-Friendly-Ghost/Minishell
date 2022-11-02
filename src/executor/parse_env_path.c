/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:34:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/02 11:23:45 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static char	*is_minishell(char *command)
{
	char	*pwd;
	char	*correct_path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (err_msg(NULL, NULL, NULL), NULL);
	correct_path = ft_strjoin(pwd, command);
	if (!correct_path)
		return (NULL);
	if (access(correct_path, F_OK | R_OK | X_OK) == 0)
		return (correct_path);
	return (NULL);
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
			correct_path = joined;
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

char	*get_executable_path(char *command_str)
{
	char	*command;
	char	*correct_path;

	if (!command_str)
		return (NULL);
	command = ft_strjoin("/", command_str);
	if (!command)
		return (NULL);
	correct_path = check_correct_path(ft_getenv("PATH"), command);
	if (!correct_path)
	{
		set_exit_code(127);
		free(command);
		if (command_str[1] == '/')
			return (err_msg(command_str, ": No such file or directory", NULL),
				NULL);
		return (err_msg(command_str, ": command not found", NULL), NULL);
	}
	return (free(command), correct_path);
}
