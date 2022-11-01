/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/31 15:52:39 by cpost         ########   odam.nl         */
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
			exit(errno);
		}
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

// static int	is_syntax_error(t_token *token_list)
// {
// 	if (token_list->type == string)
// 	{
// 		err_msg(token_list->conten, ": command not found");
// 		set_exit_code(127);
// 		return (1);
// 	}
// 	return (0);
// }

int	main(void)
{
	char				*input;
	char				**tokens;
	t_token				*token_list;

	input = NULL;
	token_list = NULL;
	// atexit(at_exit);
	get_program();
	while (1)
	{
		// set_exit_code(0);
		init_signal_handler();
		if (token_list)
			destroy_token_list(&token_list);
		input = get_input();
		tokens = lexer(input);
		free(input);
		if (!parser(tokens, &token_list))
			continue ;
		expander(token_list);
		// if (!is_syntax_error(token_list))
		exec_command(token_list, token_list->type, tokens);
		destroy_double_array(tokens);
		// print_token_list(token_list);
	}
	return (0);
}
