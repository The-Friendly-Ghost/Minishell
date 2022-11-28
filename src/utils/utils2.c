/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 09:44:10 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/28 10:26:50 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_while(char *str, char *temp, bool is_quote)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = '\0';
	while (str[i])
	{
		if (str[i] == c && is_quote)
		{
			c = '\0';
			is_quote = false;
		}
		else if ((str[i] == '\"' || str[i] == '\'') && !is_quote)
		{
			c = str[i];
			is_quote = true;
		}
		else
			temp[j++] = str[i];
		i++;
	}
}

bool	compare_no_quotes(char *token, char *cmp)
{
	char	*temp;

	if (!token)
		return (false);
	temp = ft_calloc(ft_strlen(token) + 1, sizeof(char));
	if (!temp)
		return (false);
	run_while(token, temp, false);
	if (!ft_strcmp(temp, cmp))
		return (free(temp), true);
	return (free(temp), false);
}
