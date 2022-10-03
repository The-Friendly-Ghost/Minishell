/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/03 17:19:18 by pniezen       ########   odam.nl         */
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
		if (!ft_strcmp(input, "exit"))
			exit(EXIT_SUCCESS);
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

	input = NULL;
	token_list = NULL;
	atexit(at_exit);
	get_program();
	// print_env();
	while (1)
	{
		if (token_list)
			destroy_token_list(token_list);
		input = get_input();
		tokens = lexer(input);
		free(input);
		token_list = parser(tokens);
		expander(token_list);
		print_token_list(token_list);
	}
	return (0);
}
