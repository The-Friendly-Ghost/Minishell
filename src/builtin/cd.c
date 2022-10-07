/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:39 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/07 15:38:21 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Changes the pwd to home folder if user only typed 'cd'.
 * @param none
 * @return none
 * @note
 */
static void	set_cd_home(void)
{
	t_env	**env_list;

	env_list = get_env_list();
	if (chdir(ft_getenv("HOME")) == -1);
		//return(set_error_code(errno))
	change_env_var("PWD", ft_getenv("HOME"));	
	//DEZE FUNCTIE NOG MAKEN
}

/**
 * @brief Imitates the cd command. Changes the pwd to another directory.
 * @param options Arguments
 * @return none
 * @note
 */
void	exec_cd(char **options)
{
	if (options[1] == NULL)
		return (set_cd_home());
}
