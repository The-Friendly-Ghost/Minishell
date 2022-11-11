/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/11 15:05:19 by pniezen       ########   odam.nl         */
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

static char	*get_input(char *outside_input)
{
	char		*input;

	while (1)
	{
		if (outside_input)
			input = outside_input;
		else
			input = readline("minishell> ");
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

int	main(int argc, char **argv)
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
		if (argc == 3)
			input = get_input(argv[2]);
		else
			input = get_input(NULL);
		tokens = lexer(input);
		if (argc == 1)
			free(input);
		if (!parser(tokens, &token_list))
			continue ;
		expander(token_list);
		exec_command(&token_list);
		if (argc == 3)
		 exit(get_program()->exit_code);
		//destroy_double_array(tokens);
		// print_token_list(token_list);
	}
	return (0);
}
