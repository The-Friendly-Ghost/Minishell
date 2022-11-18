/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:39 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/15 17:05:44 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

/**
 * @brief Changes the pwd to home folder if user only typed 'cd'.
 * @param none
 * @return none
 * @note
 */
static void	set_cd_home(int *cd_count)
{
	t_env	**env_list;
	char	*pwd;
	char	*cd_path;
	char	*err_str;

	env_list = get_env_list();
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno));
	cd_path = ft_getenv("HOME");
	if (!cd_path)
		return (err_msg(NULL, NULL, NULL));
	if (chdir(cd_path) == -1)
	{
		err_str = ft_strjoin(" ", strerror(errno));
		return (set_exit_code(errno),
			err_msg("cd: ", cd_path, err_str),
			free(pwd), free(err_str));
	}
	*cd_count += 1;
	change_env_var("OLDPWD", pwd, false);
	change_env_var("PWD", ft_strdup(cd_path), false);
}

/**
 * @brief Changes the pwd to the folder that the user typed in the command
 * line.
 * @param token_list the linked list with the tokens in it
 * @return false if cd faled, true if succesful. 
 * @note
 */
static bool	set_cd_path(t_token *token_list, int *cd_count)
{
	t_env	**env_list;
	char	*pwd;
	char	*err_str;

	env_list = get_env_list();
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno), false);
	if (chdir(token_list->next->content) == -1)
	{
		err_str = ft_strjoin(" ", strerror(errno));
		err_msg("cd: ", token_list->next->content, err_str);
		set_exit_code(1);
		return (free(pwd), free(err_str), false);
	}
	change_env_var("OLDPWD", pwd, false);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno), false);
	change_env_var("PWD", pwd, false);
	*cd_count += 1;
	return (true);
}

/**
 * @brief Imitates the cd command. Changes the pwd to another directory.
 * @param token_list the linked list with the tokens in it
 * @return none
 * @note
 */
void	cd_builtin(t_token *token_list)
{
	t_token		*temp;
	static int	cd_count;

	temp = token_list;
	if (!temp->next && !ft_getenv("HOME"))
		return (err_msg("cd: ", "HOME", " not set"), set_exit_code(1));
	if (temp->next == NULL || temp->next->type == is_pipe)
		return (set_cd_home(&cd_count));
	return ((void)set_cd_path(token_list, &cd_count));
}
