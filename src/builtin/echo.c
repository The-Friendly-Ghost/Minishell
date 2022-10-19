/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:18:14 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/13 11:47:29 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(char *str)
{
	char	c;
	int		i;

	c = '\0';
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && c == 0)
			c = str[i];
		else if ((str[i] == '\'' && c == '\'') || (str[i] == '\"' && c == '\"'))
			c = '\0';
		else
			write(1, &str[i], 1);
		i++;
	}
}

static bool	is_n_flag(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_builtin(t_token *token_list)
{
	t_token	*temp;
	int		nl;

	nl = 1;
	set_exit_code(0);
	temp = token_list;
	if (temp->next && is_n_flag(temp->next->content))
	{
		nl = 0;
		temp = temp->next;
		while (temp && is_n_flag(temp->content))
			temp = temp->next;
	}
	else
		temp = temp->next;
	while (temp)
	{
		print_echo(temp->content);
		if (temp->next && temp->content)
			print_echo(" ");
		temp = temp->next;
	}
	if (nl)
		print_echo("\n");
}
