/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 08:40:38 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/17 17:54:12 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"
#include <stdio.h>
#include <stdbool.h>

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
	char	c;
	int		i;
	int		count;

	c = '\0';
	i = 0;
	count = 0;
	while (str[i])
	{
		if (!c)
			c = str[i];
		if (c && is_quote(str[i]) && str[i + 1] != '\0' && i)
			count++;
		i++;
	}
	return (count);
}

bool	in_quote(char s, char c)
{
	static bool	quote;

	if (!quote && s == c)
		quote = true;
	else if (quote && s == c)
		quote = false;
	return (quote);
}

//  "str" hoi"str";
//i 0123456789
//  "str"  hoi "str" ;
//j 0123456789

char	*set_whitespace(char *str, int w_spc)
{
	bool	b_quote;
	char	*line;
	int		i;
	int		j;
	int		str_len;

	b_quote = false;
	i = 0;
	j = 0;
	str_len = ((int)ft_strlen(str) + w_spc) + 1;
	printf("%i %i %i\n", (int)ft_strlen(str), w_spc, str_len);
	line = NULL;
	if (!w_spc)
		return (str);
	line = ft_calloc(str_len, sizeof(line));
	if (!line)
		return (NULL);
	while (str[i])
	{
		if (!b_quote && str[i] == is_quote(str[i]) && str[i] != ' ')
		{
			line[j] = ' ';
			j++;
			line[j] = str[i];
			i++;
			j++;
			b_quote = true;
		}
		if (b_quote && str[i] == is_quote(str[i]) && str[i + 1] != '\0' && str[0] != ' ')
		{
			line[j] = str[i];
			i++;
			j++;
			line[j] = ' ';
			j++;
			b_quote = false;
		}
		line[j] = str[i];
		i++;
		j++;
	}
	printf("%s %i\n%s %i\n", str, i, line, j);
	return (line);
}
