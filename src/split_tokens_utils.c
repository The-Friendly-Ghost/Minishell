/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_tokens_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 12:31:03 by pniezen       #+#    #+#                 */
/*   Updated: 2022/08/23 15:34:38 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include <stdio.h>

int	is_special(char *input, int i)
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

static void	add_space(char *line, char *str, int *i, int *j)
{
	if (is_special(str, *i) == 1)
	{
		line[*j] = ' ';
		*j += 1;
		line[*j] = str[*i];
		*j += 1;
		*i += 1;
		line[*j] = ' ';
		*j += 1;
	}
	if (is_special(str, *i) == 2)
	{
		line[*j] = ' ';
		*j += 1;
		line[*j] = str[*i];
		*j += 1;
		*i += 1;
		line[*j] = str[*i];
		*j += 1;
		*i += 1;
		line[*j] = ' ';
		*j += 1;
	}
}

char	*set_whitespace(char *str, int specials_count)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_calloc(ft_strlen(str) + specials_count, sizeof(line));
	if (!line)
		return (NULL);
	while (str[i])
	{
		if (is_special(str, i))
			add_space(line, str, &i, &j);
		line[j] = str[i];
		j++;
		i++;
	}
	printf("%s;\n", str);
	return (free(str), line);
}
