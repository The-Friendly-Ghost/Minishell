/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/24 16:59:06 by cpost         ########   odam.nl         */
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
		add_history(input);
		return (input);
	}
}

static void	at_exit(void)
{
	system("leaks -q minishell");
}

int	main(void)
{
	char		*input;
	char		**tokens;
	t_token		**token_list;

	atexit(at_exit);
	get_program();
	input = NULL;
	while (1)
	{
		input = get_input();
		tokens = lexer(input);
		free(input);
		token_list = parser(tokens);
	}
	return (0);
}
