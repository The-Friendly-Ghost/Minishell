/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/07 10:53:36 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	str_is_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_whitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
		if (!str_is_whitespace(input))
			return (input);
		free(input);
	}
}

// static void	at_exit(void)
// {
// 	system("leaks -q minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		**tokens;
	t_token		*token_list;

	(void)argc;
	(void)argv;
	(void)envp;
	input = NULL;
	token_list = NULL;
	//atexit(at_exit);
	get_program();
	while (1)
	{
		if (token_list)
			destroy_token_list(&token_list);
		input = get_input();
		tokens = lexer(input);
		free(input);
		token_list = parser(tokens);
		expander(token_list);
		exec_command(token_list->type, tokens, envp);
		destroy_double_array(tokens);
		// print_token_list(token_list);
	}
	return (0);
}
