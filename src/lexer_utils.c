/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 08:40:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/23 14:03:12 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char	is_quote(char c)
{
	if (c == '\'')
		return ('\'');
	if (c == '\"')
		return ('\"');
	return ('\0');
}

static bool	reset_in_string(int *single_q, int *double_q, bool boolean_val)
{
	if (single_q)
		*single_q = 0;
	if (double_q)
		*double_q = 0;
	return (boolean_val);
}

bool	in_string(char c, bool reset)
{
	static int	single_q = 0;
	static int	double_q = 0;

	if (reset)
		return (reset_in_string(&single_q, &double_q, false));
	if (c != '\'' && c != '\"' && !single_q && !double_q)
		return (false);
	if (c == '\'' && !double_q)
	{
		single_q++;
		if (single_q == 2)
			return (reset_in_string(&single_q, NULL, true));
		return (true);
	}
	else if (c == '\"' && ! single_q)
	{
		double_q++;
		if (double_q == 2)
			return (reset_in_string(NULL, &double_q, true));
		return (true);
	}
	return (true);
}

void	skip_string(const char *str, int *i)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] != '\'' && str[*i])
			*i += 1;
		if (str[*i] == '\'')
			*i += 1;
	}
	else if (str[*i] == '\"')
	{
		*i += 1;
		while (str[*i] != '\"' && str[*i])
			*i += 1;
		if (str[*i] == '\"')
			*i += 1;
	}
}

// int	count_whitespace(char *str)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (ft_is_whitespace(str[i]) && !in_string(str[i + 1], false))
// 			count++;
// 		i++;
// 	}
// 	in_string('\0', true);
// 	return (count);
// }
