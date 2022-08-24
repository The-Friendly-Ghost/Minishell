/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/24 14:53:22 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static char	*get_input(void)
{
	const char	prompt[] = "minishell> ";
	char		*input;

	while (1)
	{
		input = readline(prompt);
		if (!input)
		{
			ft_putendl_fd("minishell> exit", 1);
			exit(EXIT_FAILURE);
		}
		if (!ft_strncmp(input, "exit", 4))
			exit(EXIT_SUCCESS);
		return (input);
	}
}

static void	at_exit(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**tokens;

	atexit(at_exit);
	(void)argc;
	(void)argv;
	(void)envp;
	input = NULL;
	while (1)
	{
		input = get_input();
		if (!input)
			continue ;
		if (tokens)
		{
			int i = 0;
			while (tokens[i])
			{
				free(tokens[i]);
				i++;
			}
			free(tokens);
		}
		tokens = lexer(input);
		free(input);
	}
	return (0);
}
