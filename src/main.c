/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 08:19:07 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/23 17:16:04 by cpost         ########   odam.nl         */
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
	t_token	*print_temp;

	//init_signals();
	get_program();
	//if (program == NULL);
		// EXIT MET ERROR CODE
	while (1)
	{
		input = get_input(input);
		token_list = parser(input);
		//expander(token_list);
		//executor(token_list);
	}
	print_temp = *token_list;
	while (print_temp->next)
	{
		printf("[%s]\n", print_temp->content);
		print_temp = print_temp->next;
	}
	return (0);
}
