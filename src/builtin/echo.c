/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:18:14 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/10 15:44:18 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%s", temp->content);
		if (temp->next && temp->content)
			printf(" ");
		temp = temp->next;
	}
	if (nl)
		printf("\n");
}
