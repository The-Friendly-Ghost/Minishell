/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_data.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 12:56:50 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/19 14:43:41 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Fills
 * @param *token A pointer to a char * (the token)
 * @return Nothing
 * @note -
 */
static void	set_environement_variables(t_env *env)
{
	extern char	**environ;

	
}

/**
 * @brief If the program struct already exists, it simply gets
 * returned. If the program isn't created yet, this function calls
 * other functions that create the program struct.
 * @param nothing
 * @return Pointer to the program struct
 * @note -
 */
t_program	*get_program(void)
{
	static t_program	program;

	if (program.env)
		return (&program);
	else
	{
		set_environement_variables(&program);
		program.exit_code = 0;
		return (&program);
	}
}
