/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:18:14 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/15 14:54:24 by pniezen       ########   odam.nl         */
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
	int	len;

	if (!str)
		return (false);
	len = ft_strlen(str);
	if (str[0] != '-')
		return (false);
	if (len > 2 && str[2] != 'n')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			return (true);
		i++;
	}
	return (false);
}

void	echo_builtin(t_token *token_list)
{
	t_token	*temp;
	int		nl;

	nl = 1;
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
	while (temp && temp->type != is_pipe)
	{
		print_echo(temp->content);
		if (temp->next && temp->content)
			print_echo(" ");
		temp = temp->next;
	}
	if (nl)
		print_echo("\n");
}
