/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:39 by cpost         #+#    #+#                 */
/*   Updated: 2022/10/06 16:27:43 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Changes the pwd to another directory
 * @param none
 * @return none
 * @note
 */
void	execute_cd(char **options)
{
	if (options[1] == NULL)
		chdir(ft_getenv("HOME"));
	
}
