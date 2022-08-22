/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/22 15:03:54 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}


static char	*get_input(char *input)
{
	while (1)
	{
		input = readline("ShitShell > ");
		if (!input)
		{
			ft_putendl_fd("minishell> exit", 2);
			// get the errno
			exit(EXIT_FAILURE);
		}
		add_history(input);
		return (input);
	}
}

int	main(void)
{
	char	*input;
	char	*tokens;
	t_token	**token_list;

	get_program();
	//if (program == NULL);
		// EXIT MET ERROR CODE
	while (1)
	{
		input = get_input(input);
		//tokens = lexer(input);
		//token_list = parser(tokens);
		//expander(token_list);
		//executor(token_list);
	}
	return (0);
}
