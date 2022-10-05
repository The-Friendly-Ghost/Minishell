/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:34:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/05 15:44:13 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_correct_path(char *path_line, char *command)
{
	char	**path_list;
	char	*correct_path;
	char	*joined;
	int		i;

	if (!path_line)
		return (NULL);
	path_list = ft_split(path_line, ':');
	if (!path_list)
		return (NULL);
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

static char	*get_correct_path(char *command)
{
	t_env	*env;
	t_env	*temp;

	env = *get_env_list();
	if (!env)
		return (NULL);
	else
		temp = env;
	while (temp)
	{
		if (temp->has_value == true && !ft_strcmp(temp->var_name, "PATH"))
			break ;
		temp = temp->next;
	}
	return (check_correct_path(temp->value, command));
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
	correct_path = get_correct_path(command);
	if (!correct_path)
		return (NULL);
	return (free(command), correct_path);
}
