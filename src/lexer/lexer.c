/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 13:38:21 by pniezen       #+#    #+#                 */
/*   Updated: 2022/11/13 11:49:19 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include <stdlib.h>
#include <stdio.h>

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
		return ;
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
		return ;
	}
}

static void	add_space_after_quote(char *line, char *str, int *i, int *j)
{
	line[*j] = str[*i];
	*j += 1;
	*i += 1;
	line[*j] = ' ';
	*j += 1;
}

static void	is_special_add_space(char *line, char *str, int *i, int *j)
{
	while (is_special(str, *i))
		add_space(line, str, i, j);
}

static char	*set_whitespace(char *str, int specials_count)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_calloc((ft_strlen(str) + specials_count) + 1, sizeof(line));
	if (!line)
		return (NULL);
	while (str[i])
	{
		if (!in_string(str[i], false))
			is_special_add_space(line, str, &i, &j);
		if (is_s_qoute_d_qoute(str, i))
		{
			if ((i > 0 && str[i] == '\"' && str[i - 1] != '\'')
				&& (i > 0 && str[i] == '\'' && str[i - 1] != '\"'))
				add_space_after_quote(line, str, &i, &j);
		}
		line[j] = str[i];
		j++;
		i++;
	}
	return (in_string('\0', true), line);
}

char	**lexer(char *input)
{
	const char	set[] = " \t\n\v\f\r";
	int			token_count;
	char		*line;
	char		**tokens;

	line = set_whitespace(input, count_specials(input));
	if (!line)
		return (NULL);
	token_count = count_whitespace(line, set) + 1;
	tokens = tokenizer(line, token_count);
	if (!(*tokens))
		exit(EXIT_FAILURE);
	return (free(line), tokens);
}
