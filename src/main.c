/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/26 13:58:20 by pniezen       ########   odam.nl         */
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
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_putendl_fd("exit", 1);
			exit(get_program()->exit_code);
		}
		add_history(input);
		if (!str_is_whitespace(input))
			return (input);
		free(input);
	}
}

int	main(void)
{
	char	*input;
	char	**tokens;
	t_token	*token_list;

	input = NULL;
	token_list = NULL;
	get_program();
	while (1)
	{
		init_signal_handler();
		destroy_token_list(&token_list);
		input = get_input();
		tokens = lexer(input);
		free(input);
		if (!parser(tokens, &token_list))
			continue ;
		expander(token_list);
		exec_command(&token_list);
	}
	return (0);
}
