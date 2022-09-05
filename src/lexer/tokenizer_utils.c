/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 12:31:03 by pniezen       #+#    #+#                 */
/*   Updated: 2022/09/05 09:35:36 by pniezen       ########   odam.nl         */
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

int	count_whitespace(char *line, const char *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (in_string(line[i], false))
			skip_string(line, &i);
		if (is_set(line[i], set))
		{
			while (is_set(line[i + 1], set) && line[i + 1])
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	is_special(char *input, int i)
{
	if (input[i] == '|' && input[i + 1] != '|')
		return (1);
	if ((input[i] == '<' && input[i + 1] != '<' && input[i + 1] != '\0')
		|| (input[i] == '>' && input[i + 1] != '>' && input[i + 1] != '\0'))
		return (1);
	if (input[i] == '<' && input[i + 1] == '<'
		&& input[i + 1] != '\0')
		return (2);
	if (input[i] == '>' && input[i + 1] == '>'
		&& input[i + 1] != '\0')
		return (2);
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

int	is_s_qoute_d_qoute(char *input, int i)
{
	if (i > 0)
	{
		if (!is_quote(input[i - 1]) && input[i] == '\'' && input[i + 1] == '\"'
			&& input[i + 1] != '\0')
			return (1);
		if (!is_quote(input[i - 1]) && input[i] == '\"' && input[i + 1] == '\''
			&& input[i + 1] != '\0')
			return (1);
	}
	return (0);
}
