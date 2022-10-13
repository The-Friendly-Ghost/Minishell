/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:39 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/13 10:45:24 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function that changes the pwd if a user typed a '~'..
 * @param token_list the linked list with the tokens in it
 * @return false if cd faled, true if succesful. 
 * @note
 */
static bool	set_cd_tilde(t_token *token_list)
{
	t_env	**env_list;
	char	*pwd;
	char	*joined;

	env_list = get_env_list();
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno), false);
	joined = ft_strjoin(ft_getenv("HOME"), token_list->next->content + 1);
	if (chdir(joined) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", joined);
		return (free(pwd), set_exit_code(1), false);
	}
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
static void	set_cd_previous(void)
{
	t_env	**env_list;
	char	*old_pwd;
	char	*pwd;

	env_list = get_env_list();
	if (old_pwd == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (set_exit_code(1));
	}
	old_pwd = ft_strdup(ft_getenv("OLDPWD"));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno));
	if (chdir(old_pwd) == -1)
	{
		printf("minishell: cd: HOME: No such file or directory\n");
		return (free(pwd), set_exit_code(1));
	}
	change_env_var("OLDPWD", pwd, false);
	change_env_var("PWD", old_pwd, false);
	printf("%s\n", old_pwd);
}

/**
 * @brief Changes the pwd to home folder if user only typed 'cd'.
 * @param none
 * @return none
 * @note
 */
static void	set_cd_home(void)
{
	t_env	**env_list;
	char	*pwd;

	env_list = get_env_list();
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno));
	if (chdir(ft_getenv("HOME")) == -1)
	{
		printf("minishell: cd: HOME: No such file or directory\n");
		return (free(pwd), set_exit_code(1));
	}
	change_env_var("OLDPWD", pwd, false);
	change_env_var("PWD", ft_getenv("HOME"), false);
}

/**
 * @brief Changes the pwd to the folder that the user typed in the command
 * line.
 * @param token_list the linked list with the tokens in it
 * @return false if cd faled, true if succesful. 
 * @note
 */
static bool	set_cd_path(t_token *token_list)
{
	t_env	**env_list;
	char	*pwd;

	env_list = get_env_list();
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno), false);
	if (chdir(token_list->next->content) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n",
			token_list->next->content);
		set_exit_code(1);
		return (free(pwd), false);
	}
<<<<<<< HEAD
	change_env_var("OLDPWD", pwd, false);
	change_env_var("PWD", token_list->next->content, false);
=======
	change_env_var("OLDPWD", pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (set_exit_code(errno), false);
	change_env_var("PWD", pwd);
>>>>>>> master
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
	t_token	*temp;

	temp = token_list;
	if (temp->next == NULL || temp->next->type == is_pipe)
		return (set_cd_home());
	else if (!ft_strcmp(temp->next->content, "-"))
		return (set_cd_previous());
	else if (!ft_strncmp(temp->next->content, "~", 1))
	{
		if (set_cd_tilde(token_list) == false)
			return (set_exit_code(1));
		return (set_exit_code(0));
	}
	else
	{
		if (set_cd_path(token_list) == false)
			return (set_exit_code(1));
		return (set_exit_code(0));
	}
}
