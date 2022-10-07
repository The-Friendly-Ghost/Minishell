/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:18:14 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/07 14:58:46 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(char **argv)
{
	int	i;
	int	nl;

	i = 0;
	nl = 0;
	set_exit_code(0);
	while (argv[i])
		i++;
	if (i > 1 && !ft_strcmp(argv[1], "-n"))
		nl = 1;
	if (i == 1)
		return ((void)printf("\n"));
	i = 1;
	while (argv[i] && i > 2)
	{
		if (i == nl)
			i++;
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (!nl)
		printf("\n");
}
