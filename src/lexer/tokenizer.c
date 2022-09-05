/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 10:34:47 by pniezen       #+#    #+#                 */
/*   Updated: 2022/09/05 09:49:22 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static char	*find_token(char **tokens, char *line, const char *set, int n)
{
	char	*tkn;
	int		i;
	int		space;

	i = 0;
	while (!is_set(line[i], set) && line[i])
	{
		if (in_string(line[i], false))
		{
			skip_string(line, &i);
			i--;
		}
		i++;
	}
	space = i;
	tkn = ft_calloc(space + 1, sizeof(char));
	if (!tkn)
		return (NULL);
	ft_strlcpy(tkn, line, space + 1);
	tokens[n] = tkn;
	return (*tokens);
}

static void	make_free(char **tokens, int n)
{
	while (n > 0)
	{
		free(tokens[n]);
		n--;
	}
}

static void	skip(char *line, const char *set, int *i)
{
	while (!is_set(line[*i], set) && line[*i])
	{
		if (in_string(line[*i], false))
			skip_string(line, i);
		(*i)++;
	}
	while (is_set(line[*i], set) && line[*i])
		(*i)++;
}

char	**tokenizer(char *line, int token_count)
{
	const char	set[] = " \t\n\v\f\r";
	char		**tokens;
	int			i;
	int			n;

	if (!line)
		return (NULL);
	tokens = ft_calloc(token_count + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	n = 0;
	while (line[i])
	{
		if (!is_set(line[i], set))
		{
			if (!find_token(tokens, line + i, set, n))
				make_free(tokens, n);
			if (in_string(line[i], false))
				skip_string(line, &i);
			n++;
		}
		skip(line, set, &i);
	}
	return (tokens);
}
