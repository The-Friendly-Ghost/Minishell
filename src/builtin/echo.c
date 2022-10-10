/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:18:14 by pniezen       #+#    #+#                 */
/*   Updated: 2022/10/10 09:28:26 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_only_n_flag(t_token *token_list, int *i, int *nl)
{
	t_token	*temp;

	temp = token_list;
	while (temp)
	{
		(*i)++;
		temp = temp->next;
	}
	if (*i > 1 && !ft_strcmp(token_list->next->content, "-n"))
		*nl = 1;
	if (*i == 1)
		return ((void)printf("\n"), 1);
	if (*i == 2 && !ft_strcmp(token_list->next->content, "-n"))
		return (1);
	return (0);
}

void	echo_builtin(t_token *token_list)
{
	t_token	*temp;
	int		i;
	int		nl;

	i = 0;
	nl = 0;
	set_exit_code(0);
	if (check_only_n_flag(token_list, &i, &nl))
		return ;
	temp = token_list->next;
	i = 1;
	while (temp)
	{
		if (i == nl)
		{
			i++;
			temp = temp->next;
		}
		printf("%s", temp->content);
		if (temp->next && temp->content)
			printf(" ");
		temp = temp->next;
	}
	if (!nl)
		printf("\n");
}
