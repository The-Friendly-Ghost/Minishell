/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/19 14:35:12 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static char	*get_input(char *input)
{
	const char	prompt[] = "minishell> ";

	while (1)
	{
		input = readline(prompt);
		if (!input)
		{
			ft_putendl_fd("minishell> exit", 1);
			// get the errno
			exit(EXIT_FAILURE);
		}
		if (!ft_strncmp(input, "exit", 5))
			exit(EXIT_SUCCESS);
		return (input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int				i;
	char			*input;

	get_program();
	//input = get_input(input);
	return (0);
}


	// split = ft_split(input, ' ');
	// i = 0;
	// while (split[i])
	// {
	// 	printf("%s", split[i]);
	// 	i++;
	// }