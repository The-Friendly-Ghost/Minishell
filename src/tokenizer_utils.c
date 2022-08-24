/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 12:31:03 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/24 11:49:23 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

int	is_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	count_whitespace(char *input, const char *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (in_string(input[i], false))
			skip_string(input, &i);
		if (is_set(input[i], set))
			count++;
		i++;
	}
	return (count);
}

int	is_special(char *input, int i)
{
	if (i > 0)
	{
		if (input[i - 1] != '|' && input[i] == '|' && input[i + 1] != '|')
			return (1);
		if ((input[i - 1] != '<' && input[i] == '<' && input[i + 1] != '<')
			|| (input[i - 1] != '>' && input[i] == '>' && input[i + 1] != '>'))
			return (1);
		if (input[i - 1] != '<' && input[i] == '<' && input[i + 1] == '<'
			&& input[i + 2] != '<' && input[i + 1] != '\0')
			return (2);
		if (input[i - 1] != '>' && input[i] == '>' && input[i + 1] == '>'
			&& input[i + 2] != '>' && input[i + 1] != '\0')
			return (2);
	}
	return (0);
}

int	count_specials(char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (is_special(input, i))
			count++;
		i++;
	}
	return (count);
}
