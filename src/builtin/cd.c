/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:39 by cpost         #+#    #+#                 */
/*   Updated: 2022/11/04 14:28:44 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

/**
 * @brief Function that changes the pwd if a user typed a '~'..
 * @param token_list the linked list with the tokens in it
 * @return false if cd faled, true if succesful. 
 * @note
 */
static bool	set_cd_tilde(t_token *token_list, int *cd_count)
{
	t_env	**env_list;
	char	*pwd;
	char	*joined;

	env_list = get_env_list();
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno), false);
	(void)token_list;
	joined = ft_strjoin(ft_getenv("HOME"), token_list->next->content + 1);
	if (!joined)
		return (free(pwd), err_msg(NULL, NULL, NULL), false);
	if (chdir(joined) == -1)
	{
		err_msg("cd: ", joined, ": No such file or directory");
		return (free(pwd), free(joined), set_exit_code(1), false);
	}
	*cd_count += 1;
	change_env_var("OLDPWD", pwd, false);
	change_env_var("PWD", joined, false);
	return (true);
}

/**
 * @brief Changes the pwd to the previous pwd. Basically, this function
 * sets pwd to the old pwd and swaps OLDPWD and PWD env variables.
 * @param none
 * @return none
 * @note
 */
static void	set_cd_previous(int *cd_count)
{
	t_env	**env_list;
	char	*old_pwd;
	char	*pwd;

	env_list = get_env_list();
	if (ft_getenv("OLDPWD") == NULL && *cd_count == 0)
		return (err_msg("cd: ", "OLDPWD", " not set"), set_exit_code(1));
	else if (ft_getenv("OLDPWD") == NULL && *cd_count > 0)
		return (change_env_var("OLDPWD", getcwd(NULL, 0), false),
			ft_putchar_fd('\n', 1));
	/* wat gebeurd hier als ft_strdup NULL returned?
	moeten we een error message naar stderr schrijven?
	err_msg(NULL, NULL, NULL) zorgt voor een Fatal error
	errno 12 -> `man errno`*/
	old_pwd = ft_strdup(ft_getenv("OLDPWD"));
	if (!old_pwd)
		return (err_msg(NULL, NULL, NULL));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno));
	if (chdir(old_pwd) == -1)
		return (free(pwd), free(old_pwd), set_exit_code(1));
	*cd_count += 1;
	change_env_var("OLDPWD", pwd, false);
	change_env_var("PWD", old_pwd, false);
	ft_putendl_fd(old_pwd, 1);
}

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
	/* wat gebeurd hier als ft_getenv NULL returned?
	moeten we een error message naar stderr schrijven?
	err_msg(NULL, NULL, NULL) zorgt voor een Fatal error
	errno 12 -> `man errno`*/
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
	else if (!ft_strcmp(temp->next->content, "-"))
		return (set_cd_previous(&cd_count));
	else if (!ft_strncmp(temp->next->content, "~", 1))
		return ((void)set_cd_tilde(token_list, &cd_count));
	else
		return ((void)set_cd_path(token_list, &cd_count));
}
