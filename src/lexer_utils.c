/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 08:40:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/20 18:05:19 by pniezen       ########   odam.nl         */
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

static bool	reset_in_quotes(int *single_q, int *double_q, bool boolean_val)
{
	if (single_q)
		*single_q = 0;
	if (double_q)
		*double_q = 0;
	return (boolean_val);
}

bool	in_quotes(char c, bool reset)
{
	static int	single_q = 0;
	static int	double_q = 0;

	if (reset)
		return (reset_in_quotes(&single_q, &double_q, false));
	if (c != '\'' && c != '\"' && !single_q && !double_q)
		return (false);
	if (c == '\'' && !double_q)
	{
		single_q++;
		if (single_q == 2)
			return (reset_in_quotes(&single_q, NULL, true));
		return (false);
	}
	else if (c == '\"' && ! single_q)
	{
		double_q++;
		if (double_q == 2)
			return (reset_in_quotes(NULL, &double_q, true));
		return (false);
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

int	count_whitespace(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!in_quotes(str[i], false) && ft_is_whitespace(str[i]))
			count++;
		i++;
	}
	return (count);
}
