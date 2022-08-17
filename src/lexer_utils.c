/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 08:40:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/17 15:44:20 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"
#include <stdio.h>

char	is_whitespace(char c)
{
	const char	dilims[] = " \t\n\v\f\r";
	int			i;

	i = 0;
	while (dilims[i])
	{
		if (dilims[i] == c)
			return (dilims[i]);
		i++;
	}
	return ('\0');
}

char	is_quote(char c)
{
	const char	dilims[] = "\'\"";
	int			i;

	i = 0;
	while (dilims[i])
	{
		if (dilims[i] == c)
			return (dilims[i]);
		i++;
	}
	return ('\0');
}

// is "een str" en "nog een str"
// 012345678910
//    012345678
// ["een str", "nog een str"]
//		0			1

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
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			count++;
		i++;
	}
	return (count);
}

//  "string" hallo"string";
//i 0123456789
//  "string"  hallo "string" ;
//j 0123456789

char	*set_whitespace(char *str, int w_spc)
{
	char	*line;
	int		i;
	int		j;
	int		str_len;
	char	quote;

	i = 0;
	j = 0;
	str_len = ft_strlen(str) + (w_spc + 1);
	line = NULL;
	if (!w_spc)
		return (str);
	line = ft_calloc(str_len, sizeof(line));
	if (!line)
		return (NULL);
	while (j < str_len && str[i])
	{
		quote = is_quote(str[i]);
		if (quote && i > 0)
		{
			line[j] = ' ';
			j++;
			while (str[i] != quote)
			{
				line [j] = str[i];
				i++;
				j++;
			}
		}
		line[j] = str[i];
		i++;
		j++;
	}
	printf("%s\n%i %i %i\n", line, i, j, str_len);
	return (line);
}
