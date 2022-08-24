/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:13:37 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/22 12:38:32 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the 
 * @param none
 * @return none
 * @note
 */
void	print_pwd(void)
{
	printf("%s\n", ft_getenv("PWD"));
}
