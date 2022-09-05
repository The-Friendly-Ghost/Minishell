/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 08:40:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/09/05 09:46:34 by pniezen       ########   odam.nl         */
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
		(*i)++;
		while (str[*i] != '\'' && str[*i])
			(*i)++;
		if (str[*i] == '\'')
			(*i)++;
		in_string(*str, true);
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"' && str[*i])
			(*i)++;
		if (str[*i] == '\"')
			(*i)++;
		in_string(*str, true);
	}
}
