/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/16 14:49:28 by pniezen       ########   odam.nl         */
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
			exit(EXIT_FAILURE);
		}
		if (!ft_strncmp(input, "exit", 5))
			exit(EXIT_SUCCESS);
		return (input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**tokens;

	(void)argc;
	(void)argv;
	(void)envp;
	input = NULL;
	while (1)
	{
		input = get_input(input);
		if (!input)
			continue ;
		tokens = lexer(input);
	}
	return (0);
}
