/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:34:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/26 15:15:47 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static char	*check_correct_path(char *path_line, char *command)
{
	char	**path_list;
	char	*correct_path;
	char	*joined;
	int		i;

	if (!path_line)
	{
		return (NULL);
	}
	path_list = ft_split(path_line, ':');
	if (!path_list)
	{
		return (NULL);
	}
	i = 0;
	while (path_list[i])
	{
		joined = ft_strjoin(path_list[i], command);
		if (!joined)
		{
			destroy_double_array(path_list);
			return (NULL);
		}
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
			return (err_msg(command_str, ": No such file or directory", NULL), NULL);
		return (err_msg(command_str, ": command not found", NULL), NULL);
	}
	return (free(command), correct_path);
}
